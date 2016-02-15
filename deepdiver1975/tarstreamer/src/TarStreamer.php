<?php

namespace ownCloud\TarStreamer;

class TarStreamer {

	const REGTYPE = 0;
	const DIRTYPE = 5;
	const XHDTYPE = 'x';

	/**
	 * Process in 1 MB chunks
	 */
	protected $blockSize = 1048576;
	protected $outStream;
	protected $needHeaders = false;

	/**
	 * Create a new TarStreamer object.
	 *
	 * @param array $options
	 */
	public function __construct($options = []){
		if (isset($options['outstream'])){
			$this->outStream = $options['outstream'];
		} else {
			$this->outStream = fopen('php://output', 'w');
			// turn off output buffering
			while (ob_get_level() > 0){
				ob_end_flush();
			}
		}
	}

	/**
	 * Send appropriate http headers before streaming the tar file and disable output buffering.
	 * This method, if used, has to be called before adding anything to the tar file.
	 *
	 * @param string $archiveName Filename of archive to be created (optional, default 'archive.tar')
	 * @param string $contentType Content mime type to be set (optional, default 'application/x-tar')
	 * @throws \Exception
	 */
	public function sendHeaders($archiveName = 'archive.tar', $contentType = 'application/x-tar'){
		$encodedArchiveName = rawurlencode($archiveName);
		if (headers_sent($headerFile, $headerLine)){
			throw new \Exception("Unable to send file $encodedArchiveName. HTML Headers have already been sent from $headerFile in line $headerLine");
		}
		$buffer = ob_get_contents();
		if (!empty($buffer)){
			throw new \Exception("Unable to send file $encodedArchiveName. Output buffer already contains text (typically warnings or errors).");
		}

		$headers = [
			'Pragma' => 'public',
			'Last-Modified' => gmdate('D, d M Y H:i:s T'),
			'Expires' => '0',
			'Accept-Ranges' => 'bytes',
			'Connection' => 'Keep-Alive',
			'Content-Type' => $contentType,
			'Cache-Control' => 'public, must-revalidate',
			'Content-Transfer-Encoding' => 'binary',
		];

		// Use UTF-8 filenames when not using Internet Explorer
		if(strpos($_SERVER['HTTP_USER_AGENT'], 'MSIE') > 0) {
			header('Content-Disposition: attachment; filename="' . rawurlencode($archiveName) . '"');
		}  else  {
			header('Content-Disposition: attachment; filename*=UTF-8\'\'' . rawurlencode($archiveName)
					. '; filename="' . rawurlencode($archiveName) . '"');
		}

		foreach ($headers as $key => $value){
			header("$key: $value");
		}
	}

	/**
	 * Add a file to the archive at the specified location and file name.
	 *
	 * @param resource $stream Stream to read data from
	 * @param string $filePath Filepath and name to be used in the archive.
	 * @param int $size
	 * @param array $options Optional, additional options
	 *                   Valid options are:
	 *                      * int timestamp: timestamp for the file (default: current time)
	 * @return bool $success
	 */
	public function addFileFromStream($stream, $filePath, $size, $options = []){
		if (!is_resource($stream) || get_resource_type($stream) != 'stream'){
			return false;
		}

		$this->initFileStreamTransfer($filePath, self::REGTYPE, $size, $options);

		// send file blocks
		while ($data = fread($stream, $this->blockSize)){
			// send data
			$this->streamFilePart($data);
		}

		// complete the file stream
		$this->completeFileStream($size);

		return true;
	}

	/**
	 * Explicitly adds a directory to the tar (necessary for empty directories)
	 *
	 * @param  string $name Name (path) of the directory
	 * @param  array  $opt  Additional options to set 
	 *                   Valid options are:
	 *                      * int timestamp: timestamp for the file (default: current time)
	 * @return void
	 */
	public function addEmptyDir($name, $opt = []){
		$opt['type'] = self::DIRTYPE;

		// send header
		$this->initFileStreamTransfer($name, self::DIRTYPE, 0, $opt);

		// complete the file stream
		$this->completeFileStream(0);
	}

	/**
	 * Close the archive.
	 * A closed archive can no longer have new files added to it. After
	 * closing, the file is completely written to the output stream.
	 * @return bool $success */
	public function finalize(){
		// tar requires the end of the file have two 512 byte null blocks
		$this->send(pack('a1024', ''));

		// flush the data to the output
		fflush($this->outStream);
		return true;
	}

	/**
	 * Initialize a file stream
	 *
	 * @param string $name file path or just name
	 * @param int $type type of the item
	 * @param int $size size in bytes of the file
	 * @param array $opt array  (optional)
	 *                   Valid options are:
	 *                      * int timestamp: timestamp for the file (default: current time)
	 */
	protected function initFileStreamTransfer($name, $type, $size, $opt = []){
		$dirName = (dirname($name) == '.') ? '' : dirname($name);
		$fileName = ($type == self::DIRTYPE) ? basename($name) . '/' : basename($name);


		// handle long file names via PAX
		if (strlen($fileName) > 99 || strlen($dirName) > 154){
			$pax = $this->paxGenerate([ 'path' => $dirName . '/' . $fileName]);
			$paxSize = strlen($pax);

			$this->initFileStreamTransfer('', self::XHDTYPE, $paxSize);

			$this->streamFilePart($pax);
			$this->completeFileStream($paxSize);
		}

		// process optional arguments
		$time = isset($opt['timestamp']) ? $opt['timestamp'] : time();

		// build data descriptor
		$fields = [
			['a100', substr($fileName, 0, 100)],
			['a8', str_pad('777', 7, '0', STR_PAD_LEFT)],
			['a8', decoct(str_pad('0', 7, '0', STR_PAD_LEFT))],
			['a8', decoct(str_pad('0', 7, '0', STR_PAD_LEFT))],
			['a12', str_pad(decoct($size), 11, '0', STR_PAD_LEFT)],
			['a12', str_pad(decoct($time), 11, '0', STR_PAD_LEFT)],
			['a8', ''],
			['a1', $type],
			['a100', ''],
			['a6', 'ustar'],
			['a2', '00'],
			['a32', ''],
			['a32', ''],
			['a8', ''],
			['a8', ''],
			['a155', substr($dirName, 0, 155)],
			['a12', ''],
		];

		// pack fields and calculate "total" length
		$header = $this->packFields($fields);

		// Compute header checksum
		$checksum = str_pad(decoct($this->computeUnsignedChecksum($header)), 6, "0", STR_PAD_LEFT);
		for ($i = 0; $i < 6; $i++){
			$header[(148 + $i)] = substr($checksum, $i, 1);
		}
		$header[154] = chr(0);
		$header[155] = chr(32);

		// print header
		$this->send($header);
	}

	/**
	 * Stream the next part of the current file stream.
	 *
	 * @param string $data raw data to send
	 */
	protected function streamFilePart($data){
		// send data
		$this->send($data);

		// flush the data to the output
		fflush($this->outStream);
	}

	/**
	 * Complete the current file stream
	 * @param $size
	 */
	protected function completeFileStream($size){
		// ensure we pad the last block so that it is 512 bytes
		if (($mod = ($size % 512)) > 0){
			$this->send(pack('a' . (512 - $mod), ''));
		}

		// flush the data to the output
		fflush($this->outStream);
	}

	/**
	 * Send string, sending HTTP headers if necessary.
	 *
	 * @param string $data data to send
	 */
	protected function send($data){
		if ($this->needHeaders){
			$this->sendHeaders();
		}
		$this->needHeaders = false;

		fwrite($this->outStream, $data);
	}

	/**
	 * Create a format string and argument list for pack(), then call pack() and return the result.
	 *
	 * @param array $fields key being the format string and value being the data to pack
	 * @return string binary packed data returned from pack()
	 */
	protected function packFields($fields){
		list ($fmt, $args) = ['', []];

		// populate format string and argument list
		foreach ($fields as $field){
			$fmt .= $field[0];
			$args[] = $field[1];
		}

		// prepend format string to argument list
		array_unshift($args, $fmt);

		// build output string from header and compressed data
		return call_user_func_array('pack', $args);
	}

	/**
	 * Generate unsigned checksum of header
	 *
	 * @param string $header
	 * @return string unsigned checksum
	 */
	protected function computeUnsignedChecksum($header){
		$unsignedChecksum = 0;
		for ($i = 0; $i < 512; $i++){
			$unsignedChecksum += ord($header[$i]);
		}
		for ($i = 0; $i < 8; $i++){
			$unsignedChecksum -= ord($header[148 + $i]);
		}
		$unsignedChecksum += ord(" ") * 8;

		return $unsignedChecksum;
	}

	/**
	 * Generate a PAX string
	 *
	 * @param array $fields key value mapping
	 * @return string PAX formated string
	 * @link http://www.freebsd.org/cgi/man.cgi?query=tar&sektion=5&manpath=FreeBSD+8-current tar / PAX spec
	 */
	protected function paxGenerate($fields){
		$lines = '';
		foreach ($fields as $name => $value){
			// build the line and the size
			$line = ' ' . $name . '=' . $value . "\n";
			$size = strlen(strlen($line)) + strlen($line);

			// add the line
			$lines .= $size . $line;
		}

		return $lines;
	}
}
