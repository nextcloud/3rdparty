<?php
/////////////////////////////////////////////////////////////////
/// getID3() by James Heinrich <info@getid3.org>               //
//  available at http://getid3.sourceforge.net                 //
//            or http://www.getid3.org                         //
//          also https://github.com/JamesHeinrich/getID3       //
/////////////////////////////////////////////////////////////////

namespace ID3Parser;

use ID3Parser\getID3\getID3;

class ID3Parser {
	/**
	 * @param string $fileName
	 * @return array
	 */
	public function analyze($fileName) {
		$getID3 = new getID3();
		return $getID3->analyze($fileName);
	}
}
