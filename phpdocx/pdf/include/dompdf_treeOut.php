<?php
/*
depende de dompdf 0.5.2 beta2

#MOD# se ha añadido el metodo "get_props($prop)" a "style.cls.php", para poder recuperar algunas propiedades CSS limpias
*/
  /**
   * Getter para el array _props[]
   * #MOD#
   * Alguna informacion de estilo (como font_family) no se puede recuperar original, tal como se encuentra en el array _props[], este metodo lo permite
   * Devuelve false si no existe la propiedad pedida.
   *
   * @param string $prop Propiedad CSS a recuperar
   * @return string
   */
/*  function get_props($prop) {
	  if(isset($this->_prop_cache[$prop])) return($this->_prop_cache[$prop]);
	  elseif(isset($this->_props[$prop])) return($this->_props[$prop]);
	  else return(false);
  }
*/

/**
 * Export DOMPdf tree
 */
class dompdf_treeOut extends DOMPDF {
	/**
	 * [OVERWRITE]
	 * @var string The system's locale
	 */
	private $_system_locale = null;

	/**
	 * [OVERWRITE]
	 * @var bool Tells if the system's locale is the C standard one
	 */
	private $_locale_standard = false;

	/**
	 * Simple DOMPdf tree
	 *
	 * @var array
	 * @access private
	 * @see dompdf_treeOut::getDompdfTree()
	 */
	private $aDompdfTree;

	/**
	 * Class constructor
	 */
	public function __construct(){
		$this->aDompdfTree = array();

		parent::__construct();
	}

	/**
	 * Class destructor
	 */
	public function __destruct(){
		if(method_exists('DOMPDF', '__destruct')) parent::__destruct();
	}

	/**
	 * Save the system's locale configuration and
	 * set the right value for numeric formatting
	 * [OVERWRITE]
	 */
	private function save_locale() {
		if ( $this->_locale_standard ) return;

		$this->_system_locale = setlocale(LC_NUMERIC, "C");
	}

	/**
	 * Restore the system's locale configuration
	 * [OVERWRITE]
	 */
	private function restore_locale() {
		if ( $this->_locale_standard ) return;

		setlocale(LC_NUMERIC, $this->_system_locale);
	}

	/**
	 * Loads an HTML file
	 * [OVERWRITE]
	 *
	 * Parse errors are stored in the global array _dompdf_warnings.
	 *
	 * @param string $file a filename or url to load
	 */
	function load_html_file($file) {
		$this->save_locale();

		// Store parsing warnings as messages (this is to prevent output to the
		// browser if the html is ugly and the dom extension complains,
		// preventing the pdf from being streamed.)
		if ( !$this->_protocol && !$this->_base_host && !$this->_base_path )
			list($this->_protocol, $this->_base_host, $this->_base_path) = explode_url($file);

		if ( !DOMPDF_ENABLE_REMOTE && ($this->_protocol != "" && $this->_protocol !== "file://" ) )
			throw new DOMPDF_Exception("Remote file requested, but DOMPDF_ENABLE_REMOTE is false.");

		if ($this->_protocol == "" || $this->_protocol === "file://") {

			$realfile = realpath($file);
			if ( !$file )
				throw new DOMPDF_Exception("File '$file' not found.");

			if ( strpos($realfile, DOMPDF_CHROOT) !== 0 )
				throw new DOMPDF_Exception("Permission denied on $file.");

			// Exclude dot files (e.g. .htaccess)
			if ( substr(basename($realfile),0,1) === "." )
				throw new DOMPDF_Exception("Permission denied on $file.");

			$file = $realfile;
		}

		$context = stream_context_create(array('http'=>array(
			'method' => 'GET',
			'user_agent' => 'PHPDocX-getFile',
			'header'=>'Connection: close',
			'timeout' => 1
		)));
		//$contents = file_get_contents(urldecode($file), false, $context);
		$contents = file_get_contents(urldecode($file), false);
		$encoding = null;

		// See http://the-stickman.com/web-development/php/getting-http-response-headers-when-using-file_get_contents/
		if ( isset($http_response_header) ) {
			foreach($http_response_header as $_header) {
				if ( preg_match("@Content-Type:\s*[\w/]+;\s*?charset=([^\s]+)@i", $_header, $matches) ) {
					$encoding = strtoupper($matches[1]);
					break;
				}
			}
		}

		$this->restore_locale();

		$this->load_html($contents, $encoding);
	}

	/**
	 * Loads an HTML string
	 * [OVERWRITE]
	 *
	 * Parse errors are stored in the global array _dompdf_warnings.
	 *
	 * @param string $str HTML text to load
	 */
	function load_html($str, $encoding = null) {
		$this->save_locale();

		$encoding = mb_detect_encoding($str, mb_list_encodings(), true);
		if ($encoding !== 'UTF-8') {
			$metatags = array(
			'@<meta\s+http-equiv="Content-Type"\s+content="(?:[\w/]+)(?:;\s*?charset=([^\s"]+))?@i',
			'@<meta\s+content="(?:[\w/]+)(?:;\s*?charset=([^\s"]+))"?\s+http-equiv="Content-Type"@i',
			);

			foreach($metatags as $metatag) {
				if (preg_match($metatag, $str, $matches)) break;
			}

			//redetecta segun metas
			if (empty($encoding)) {
				if (isset($matches[1])) {
					$encoding = strtoupper($matches[1]);
				} else {
					$encoding = 'UTF-8';
				}
			} else {
				if (isset($matches[1])) {
					$encoding = strtoupper($matches[1]);
				} else {
					$encoding = 'auto';
				}
			}

			if($encoding != 'UTF-8') $str = mb_convert_encoding($str, 'UTF-8', $encoding);

			if (isset($matches[1])) {
				$str = preg_replace('/charset=([^\s"]+)/i','charset=UTF-8', $str);
			} else {
				$str = str_replace('<head>', '<head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8">', $str);
			}
		}
		

		// Parse embedded php, first-pass
		if ( DOMPDF_ENABLE_PHP ) {
			ob_start();
			eval("?" . ">$str");
			$str = ob_get_clean();
		}


		// if the document contains non utf-8 with a utf-8 meta tag chars and was
		// detected as utf-8 by mbstring, problems could happen.
		// http://devzone.zend.com/article/8855
		if ( $encoding === 'UTF-8' ) {
			$str = preg_replace("/<meta([^>]+)>/", "", $str);
		}

		$str = $this->_load_html($str);

		// Store parsing warnings as messages
		set_error_handler("record_warnings");
		$str = mb_convert_encoding($str, 'HTML-ENTITIES', 'UTF-8'); //DOMDocument::loadHTML tiene problemas con cadenas en utf 8
		$this->_xml->loadHTML($str);
		restore_error_handler();

		$this->restore_locale();
	}

	/**
	 * Normalizes an HTML string
	 *
	 * @param string $str HTML text to load
	 */
	private function _load_html($str){
		//$str = mb_detect_encoding($str, 'UTF-8', true) == 'UTF-8' ? utf8_decode($str) : $str;

		try{
			$tidy = new tidy();
			$tidy = tidy_parse_string($str, array('output-xhtml' => TRUE), 'utf8');
			//$tidy->cleanRepair();
			$html = $tidy->html();
			$str = $html->value;
		}
		catch(Exception $e){
			//avisar al usuario de que no esta disponible tidy
			//throw new DOMPDF_Exception("Tidy library not available.");

			$doc = new DOMDocument();
			$doc->loadHTML($str);
			$str = @$doc->saveHTML();
		}
		//$str = preg_replace('/$(\s*?)(\S)/m', ' \2', $str);
		//$str = preg_replace('/>(\s*?)</me', "strpos('$0', ' ') !== false?'> <':'><'", $str);
		$str = preg_replace('/>(\s*$\s*)</me', "strpos('$0', ' ') === false?'><':'> <'", $str);

		$str = str_replace('</body>', '<close></body>', $str);

		//parent::load_html($str);
		return($str);
	}

	public function render($filter = '*'){
		//$sRet = '';

		$this->_process_html();
		$this->_css->apply_styles($this->_tree);

		foreach($this->_tree->get_frames() as $frame){
			print_r($frame);
			$this->aDompdfTree = $this->_render($frame, $filter);
			break;
		}

		return(true);
	}

	/**
	 * Render frames recursively
	 *
	 * @param Frame $frame The frame to render
	 */
	private function _render(Frame $frame, $filter){
		$aDompdfTree = array();

		$node = $frame->get_node();

		switch($node->nodeName){
			case 'caption': //ignore these tags
			case 'meta':
			case 'script':
			case 'title':
				break;
			case '#text':
			case 'a':
			case 'br':
			case 'dd':
			case 'div':
			case 'dl':
			case 'dt':
			case 'h1':
			case 'h2':
			case 'h3':
			case 'h4':
			case 'h5':
			case 'h6':
			case 'li':
			case 'ol':
			case 'p':
			case 'table':
			case 'td':
			case 'th':
			case 'tr':
			case 'ul':
			case 'img':
			case 'img_inner':
				$aDompdfTree['nodeName'] = $node->nodeName;
				$aDompdfTree['nodeValue'] = $node->nodeValue;
				$aDompdfTree['attributes'] = $this->getAttributes($node);
				$aDompdfTree['properties'] = $this->getProperties($frame->get_style());

				$filter = $this->filterTreeOut($aDompdfTree, $filter);
				if($filter != '*') $aDompdfTree['nodeName'] .= '_noPaint';

				$aTempTree = array();
				foreach($frame->get_children() as $child){
					$aTemp = $this->_render($child, $filter);
					if(!empty($aTemp)) $aTempTree[] = $aTemp;
				}
				$aDompdfTree['children'] = empty($aTempTree)?array():$aTempTree;
				return($aDompdfTree);
				break;
			case 'close':
				$aDompdfTree['nodeName'] = $node->nodeName;
				foreach($frame->get_children() as $child){
					$aTemp = $this->_render($child, $filter);
					if(!empty($aTemp)) $aTempTree[] = $aTemp;
				}
				$aDompdfTree['children'] = empty($aTempTree)?array():$aTempTree;
				return($aDompdfTree);
				break;
			default:
				$aDompdfTree['nodeName'] = $node->nodeName;

				$filter = $this->filterTreeOut($aDompdfTree, $filter);
				if($filter != '*') $aDompdfTree['nodeName'] .= '_noPaint';

				foreach($frame->get_children() as $child){
					$aTemp = $this->_render($child, $filter);
					if(!empty($aTemp)) $aTempTree[] = $aTemp;
				}
				$aDompdfTree['children'] = empty($aTempTree)?array():$aTempTree;
				return($aDompdfTree);
				break;
		}

		return(false);
	}

	/*
	 * Filter the tree
	 * Filter by ".css_class" or "#dom_id" or "<html_tag>" (if not prefix filter both)
	 *
	 * @access private
	 * @return string
	 */
	private function filterTreeOut($aDompdfTree, $filter){
		/*if($filter == '*' || (isset($aDompdfTree['attributes']['id']) && $filter == $aDompdfTree['attributes']['id']) || in_array($filter, $aDompdfTree['attributes']['class'])) $filter = '*';
		else $aDompdfTree['nodeName'] .= '_noPaint';*/

		if($filter != '*'){
			if(is_array($filter)){
				foreach($filter as $filter_element){
					if((isset($aDompdfTree['attributes']['id']) && $aDompdfTree['attributes']['id'] == $filter_element) || (isset($aDompdfTree['attributes']['class']) && in_array($filter_element, $aDompdfTree['attributes']['class'])) || (isset($aDompdfTree['nodeName']) && $filter_element == $aDompdfTree['nodeName'])){$filter = '*';break;}
					elseif(strpos($filter_element, '#') === 0 && isset($aDompdfTree['attributes']['id']) && ltrim($filter_element, '#') == $aDompdfTree['attributes']['id']){$filter = '*';break;}
					elseif(strpos($filter_element, '.') === 0 && isset($aDompdfTree['attributes']['class']) && in_array(ltrim($filter_element, '.'), $aDompdfTree['attributes']['class'])){$filter = '*';break;}
					elseif(strpos($filter_element, '<') === 0 && isset($aDompdfTree['nodeName']) && trim($filter_element, '<>') == $aDompdfTree['nodeName']){$filter = '*';break;}
				}
			}
			else{
				if((isset($aDompdfTree['attributes']['id']) && $aDompdfTree['attributes']['id'] == $filter) || (isset($aDompdfTree['attributes']['class']) && in_array($filter, $aDompdfTree['attributes']['class'])) || (isset($aDompdfTree['nodeName']) && $filter == $aDompdfTree['nodeName'])) $filter = '*';
				elseif(strpos($filter, '#') === 0 && isset($aDompdfTree['attributes']['id']) && ltrim($filter, '#') == $aDompdfTree['attributes']['id']) $filter = '*';
				elseif(strpos($filter, '.') === 0 && isset($aDompdfTree['attributes']['class']) && in_array(ltrim($filter, '.'), $aDompdfTree['attributes']['class'])) $filter = '*';
				elseif(strpos($filter, '<') === 0 && isset($aDompdfTree['nodeName']) && trim($filter, '<>') == $aDompdfTree['nodeName']) $filter = '*';
			}
		}
		return($filter);
	}

	private function getAttributes($node){
		$aRet = array();
		$temp = false;

		switch($node->nodeName){
			case '#text':
				return($aRet);
				break;
			case 'form':
				$action = $node->getAttribute('action');
				$aRet['action'] = empty($action)?'#':$action;
				$method = $node->getAttribute('method');
				$aRet['method'] = empty($method)?'post':$method;
				break;
			case 'table':
				$aRet['border'] = (string)$node->getAttribute('border');
				break;
			case 'td':
			case 'th':
				$colspan = (int)$node->getAttribute('colspan');
				$aRet['colspan'] = empty($colspan)?1:$colspan;
				$rowspan = (int)$node->getAttribute('rowspan');
				$aRet['rowspan'] = empty($rowspan)?1:$rowspan;
				break;
			case 'a':
				$aRet['href'] = (string)$node->getAttribute('href');
				break;
			case 'img':
				$aRet['src'] = (string)$node->getAttribute('src');
				break;
			case 'img_inner':
				$aRet['src'] = (string)$node->getAttribute('src');
				break;
			default:
		}

		$temp = $node->getAttribute('id');
		if($temp){$aRet['id'] = $temp;$temp = false;}

		$temp = $node->getAttribute('name');
		if($temp){$aRet['name'] = $temp;$temp = false;}

		$temp = $node->getAttribute('title');
		if($temp){$aRet['title'] = $temp;$temp = false;}

		$temp = $node->getAttribute('alt');
		if($temp){$aRet['alt'] = $temp;$temp = false;}

		$temp = $node->getAttribute('class');
		if($temp){
			$aRet['class'] = explode(' ', $temp);
			$temp = false;
		}

		return($aRet);
	}

	private function getProperties($properties){
		$aRet = array();

		//valid styles
		$aStyles = array('azimuth', 'background_attachment', 'background_color', 'background_image', 'background_position', 'background_repeat',
		'background', 'border_collapse', 'border_color', 'border_spacing', 'border_style', 'border_top', 'border_right', 'border_bottom', 'border_left',
		'border_top_color', 'border_right_color', 'border_bottom_color', 'border_left_color', 'border_top_style', 'border_right_style', 'border_bottom_style',
		'border_left_style', 'border_top_width', 'border_right_width', 'border_bottom_width', 'border_left_width', 'border_width', 'border', 'bottom',
		'caption_side', 'clear', 'clip', 'color', 'content', 'counter_increment', 'counter_reset', 'cue_after', 'cue_before', 'cue', 'cursor', 'direction',
		'display', 'elevation', 'empty_cells', 'float', 'font_family', 'font_size', 'font_style', 'font_variant', 'font_weight', 'font', 'height', 'left',
		'letter_spacing', 'line_height', 'list_style_image', 'list_style_position', 'list_style_type', 'list_style', 'margin_right', 'margin_left', 'margin_top',
		'margin_bottom', 'margin', 'max_height', 'max_width', 'min_height', 'min_width', 'orphans', 'outline_color', 'outline_style', 'outline_width', 'outline',
		'overflow', 'padding_top', 'padding_right', 'padding_bottom', 'padding_left', 'padding', 'page_break_after', 'page_break_before', 'page_break_inside',
		'pause_after', 'pause_before', 'pause', 'pitch_range', 'pitch', 'play_during', 'position', 'quotes', 'richness', 'right', 'speak_header', 'speak_numeral',
		'speak_punctuation', 'speak', 'speech_rate', 'stress', 'table_layout', 'text_align', 'text_decoration', 'text_indent', 'text_transform', 'top',
		'unicode_bidi', 'vertical_align', 'visibility', 'voice_family', 'volume', 'white_space', 'widows', 'width', 'word_spacing', 'z_index');

		foreach($aStyles as $style){
			if($style == 'font_family') $sTemp = $properties->get_props($style);
			else{
				try{$sTemp = $properties->$style;}
				catch(Exception $e){$sTemp = '';}
			}
			if($sTemp != ''){
				$aRet[$style] = $sTemp;
			}
		}

		return($aRet);
	}

	public function getDompdfTree($html = '', $isfile = false, $filter = '*'){

		if(!empty($html)){
			if($isfile) {
				$this->load_html_file(urldecode($html));
			}
			else {
				$this->load_html($html);
			}

			$this->render($filter);
		}
		elseif(empty($this->aDompdfTree)) {
			$this->render($filter);
		}

		return($this->aDompdfTree);
	}

}
