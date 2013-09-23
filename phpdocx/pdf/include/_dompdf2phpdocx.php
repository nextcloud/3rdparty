<?php
/*
depende de dompdf 0.5.2 beta2
*/

/**
 * phpdocx renderer
 */
class dompdf2phpdocx extends DOMPDF {
	public static $openTags;
	public static $openPs;
	public static $openTable;
	public static $WordML;

	/**
	 * Class constructor
	 */
	public function __construct(){
		parent::__construct();

		self::$openTags = array();
		self::$openPs = false;
		self::$openTable = array();
		self::$WordML = '';
	}

	/**
	 * Class destructor
	 */
	public function __destruct(){
		if(method_exists('DOMPDF', '__destruct')) parent::__destruct();
	}

	/**
	 * Loads an HTML string
	 *
	 * @param string $str HTML text to load
	 */
	function load_html($str){
		try{
			$tidy = new tidy();
			$tidy = tidy_parse_string($str);
			//$tidy->cleanRepair();
			$html = $tidy->html();
			$str = $html->value;
		}
		catch(Exception $e){
			//avisar al usuario de que no esta disponible tidy
			$doc = new DOMDocument();
			$doc->loadHTML($str);
			$str = @$doc->saveHTML();
		}
		$str = preg_replace('/>\s*?</', '><', $str);

		$str = str_replace('</body>', '<close></body>', $str);
		parent::load_html($str);
	}

	public function render(){
		//$sRet = '';

		$this->_process_html();
		$this->_css->apply_styles($this->_tree);

		foreach($this->_tree->get_frames() as $frame){
			/*$node = $frame->get_node();
			var_dump($node->nodeName);/**/
			//$sRet .= $this->_render($frame);
			$this->_render($frame);
			break;
		}
		return(self::$WordML);
	}

	/**
	 * Render frames recursively
	 *
	 * @param Frame $frame the frame to render
	 */
	private function _render(Frame $frame, $depth=0){
		//$sRet = '';

		$this->_level = $depth;
		$node = $frame->get_node();
		$properties = $frame->get_style();

		$this->countTags = array_count_values(self::$openTags);

		switch($node->nodeName){
			case 'p':
			case 'div':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				if(self::$openPs){
					self::$WordML .= '</w:p><w:p>';
				}else{
					self::$WordML .= '<w:p>'; 
					self::$openPs = true;
				}
				self::$WordML .= $this->generatePPr($properties);
				self::$openTags[$depth] = $node->nodeName;
				break;
			case 'ul':
			case 'ol':
				self::$openTags[$depth] = $node->nodeName;
				break;
			case 'li':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				if(self::$openPs){
					self::$WordML .= '</w:p><w:p>';
				}else{
					self::$WordML .= '<w:p>';
					self::$openPs = true;
				}
				self::$WordML .= $this->generateListPr($properties);
				self::$openTags[$depth] = $node->nodeName;
				break;
			case 'table':
				self::$openTable = array(); //TODO cambiar para tablas anidadas
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				if(self::$openPs){
					self::$WordML .= '</w:p><w:tbl>';
					self::$openPs = false;
				}else{
					self::$WordML .= '<w:tbl>';
				}
				self::$WordML .= $this->generateTblPr($properties);
				self::$openTags[$depth] = $node->nodeName;
				break; 
			case 'tr':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				array_push(self::$openTable, array());
				self::$WordML .= '<w:tr>';
				self::$WordML .= $this->generateTrPr($properties);
				self::$openTags[$depth] = $node->nodeName;
				break;
			case 'td':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				$firstRow = false;
				//Now we have to deal with the details associated to the rowspan and colspan of this table cell
				$colspan = (int)$node->getAttribute('colspan');
				$colspan = empty($colspan)?1:$colspan;
				$rowspan = (int)$node->getAttribute('rowspan');
				$rowspan = empty($rowspan)?1:$rowspan;

				$row = count(self::$openTable) -1;
				$column = count(self::$openTable[$row]);
				$vmerge = $this->countEmptyColumns($row, $column);
				for($k=0; $k < $colspan; $k++){
					array_push(self::$openTable[count(self::$openTable)-1], $rowspan);
				}
				if($vmerge > 0){
					self::$WordML .= '<w:tc><w:tcPr><w:gridSpan  w:val="'.$vmerge.'" /><w:vMerge w:val="continue" /></w:tcPr><w:p /></w:tc>';
				}
				self::$WordML .= '<w:tc>';
				self::$WordML .= $this->generateTcPr($properties, $colspan, $rowspan, $firstRow); //FIXME
				self::$openTags[$depth] = $node->nodeName;
				break;
			case 'th':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				$firstRow = true; 
				//Now we have to deal with the details associated to the rowspan and colspan of this table cell 
				$colspan = (int)$node->getAttribute('colspan');
				$colspan = empty($colspan)?1:$colspan;
				$rowspan = (int)$node->getAttribute('rowspan');
				$rowspan = empty($rowspan)?1:$rowspan;

				$row = count(self::$openTable) -1;
				$column = count(self::$openTable[$row]);
				$vmerge = $this->countEmptyColumns($row,$column);
				for($k=0; $k < $colspan; $k++){
					array_push(self::$openTable[count(self::$openTable)-1], $rowspan);
				}
				if($vmerge > 0){
					self::$WordML .= '<w:tc><w:tcPr><w:gridSpan  w:val="'.$vmerge.'" /><w:vMerge w:val="continue" /></w:tcPr><w:p /></w:tc>';
				}
				self::$WordML .= '<w:tc>';
				self::$WordML .= $this->generateTcPr($properties, $colspan, $rowspan, $firstRow); //FIXME
				self::$openTags[$depth] = $node->nodeName; 
				break;
			case '#text':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				if(self::$openPs){
					self::$WordML .= '<w:r>';
				}else{
					self::$WordML .= '<w:p>';
					self::$WordML .= $this->generatePPr($properties);
					self::$WordML .= '<w:r>';
					self::$openPs = true;
				}
				self::$WordML .= $this->generateRPr($properties);
				self::$WordML .= '<w:t>'.htmlspecialchars($node->nodeValue);
				self::$WordML .= '</w:t></w:r>';
				self::$openTags[$depth] = $node->nodeName;
				break;
			case 'br':
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				if(self::$openPs){
					self::$WordML .= '<w:r><w:br /><w:t></w:t></w:r>';
				}else{
					self::$WordML .= '<w:p />';
				}
				break;
			case 'close':
				//if(strpos(self::$WordML, '#<w:gridCol/>#') !== false) self::$WordML = str_replace('#<w:gridCol/>#', '<w:gridCol/>', self::$WordML); //TODO forzar limpieza de columnas de tabla?
				self::$WordML .= $this->closePreviousTags($depth, $node->nodeName);
				break;
			default:
				self::$openTags[$depth] = $node->nodeName;
				break;
		}

		++$depth;
		foreach($frame->get_children() as $child){
			//var_dump(gettype($child));
			$this->_render($child, $depth);
		}
	}

	private function closePreviousTags($depth,$currentTag=''){
		$sRet = '';

		$counter = count(self::$openTags);
		for($j = $counter; $j >= $depth -1 ; $j--){
			$tag = array_pop(self::$openTags);

			switch($tag){
				case 'p':
				case 'div':
				case 'li':
					if(self::$openPs){
						$sRet .= '</w:p>';
						self::$openPs = false;
					}
					break;
				case 'table':
					if(self::$openPs){
						$sRet .= '</w:p></w:tbl>';
						self::$openPs = false;
					}else{
						$sRet .= '</w:tbl>';
					}
					break; 
				case 'tr':
					//Before closing a row we should make sure that there are no laking cells due to a previous rowspan
					$row = count(self::$openTable) -1;
					$column = count(self::$openTable[$row]);
					$numberRows = 0;
					if($row >= 1){
						$numberRows = count(self::$openTable[$row-1]) - count(self::$openTable[$row]);
						if($numberRows > 0){
							$sRet .= '<w:tc><w:tcPr><w:gridSpan  w:val="'.$numberRows.'" /><w:vMerge w:val="continue" /></w:tcPr><w:p /></w:tc>';
						}
						for($k = 0; $k < $numberRows; $k++){
							array_push(self::$openTable[$row], self::$openTable[$row-1][$column + $k]-1 );
						}
					}
					if(strpos(self::$WordML, '#<w:gridCol/>#') !== false) self::$WordML = str_replace('#<w:gridCol/>#', str_repeat('<w:gridCol/>', ($column + $numberRows)), self::$WordML);
					//We now may close the tr tag
					$sRet .= '</w:tr>';
					break;
				case 'td':
					if(self::$openPs){
						$sRet .= '</w:p></w:tc>';
						self::$openPs = false;
					}else{
						$sRet .= '</w:tc>';
					}
					break;
				case 'th':
					if(self::$openPs){
						$sRet .= '</w:p></w:tc>';
						self::$openPs = false;
					}else{
						$sRet .= '</w:tc>';
					}
					break;
				case '#text':
					if($currentTag == 'close'){
						$sRet .= '</w:p>';
						self::$openPs = false;
					}
			}
		}

		return($sRet);
	}

	private function listStyle(){
		return 'listParagraph';
	}

	private function listType($tipo = array(1,2)){
		$counter = count(self::$openTags) ;
		for($j = $counter; $j >= ($this->_level -1) ; $j--){
			if(@self::$openTags[$j] == 'ul'){
				$num = $tipo[0];
				break;
			}else if(@self::$openTags[$j] == 'ol'){
				$num = $tipo[1];
				break;
			}
		}
		if(isset($num)){
			return $num; 
		}else{
			return $tipo[0];
		}
	}

	private function generatePPr($properties){
		$stringPPr = '<w:pPr>';
		//TODO: write properties
		$stringPPr .= '</w:pPr>';
		return $stringPPr;
	}

	private function generateRPr($properties){
		$stringRPr = '<w:rPr>';
		//By the time being we only parse the color and if the font is bold or italic
		if(@$properties->__get('font_weight') == 'bolder'){
			$stringRPr .='<w:b />';
		}
		if(@$properties->__get('font_style') == 'italic'){
			$stringRPr .='<w:i />';
		}
		if(@$properties->__get('color') != '' && is_array($properties->__get('color'))){
			$color = $properties->__get('color');
			$color = str_replace('#','',$color["hex"]);
			$stringRPr .='<w:color w:val="'.$color.'" />';
		}
		if(@$properties->__get('font_size') != ''){
			$stringRPr .='<w:sz w:val="'.($properties->__get('font_size') * 2).'" />';
		}
		$stringRPr .= '</w:rPr>';
		return $stringRPr;
	}

	private function generateTblPr($properties){
		$stringTblPr = '<w:tblPr>';
		//TODO: write properties
		$stringTblPr .= '</w:tblPr>';
		$stringTblPr .= '<w:tblGrid>#<w:gridCol/>#</w:tblGrid>';
		return $stringTblPr;
	}

	private function generateTrPr($properties){
		$stringTrPr = '<w:trPr>';
		//TODO: write properties
		$stringTrPr .= '</w:trPr>';
		return $stringTrPr;
	}

	private function generateTcPr($properties, $colspan, $rowspan, $firstRow){
		$stringTcPr = '<w:tcPr>';
		if($colspan > 1){
			$stringTcPr .= '<w:gridSpan  w:val="'.$colspan.'" />';
		}
		if($rowspan > 1){
			$stringTcPr .= '<w:vMerge w:val="restart" />';
		}
		if(@$properties->__get('background_color') != '' && is_array($properties->__get('background_color'))){
			$color = $properties->__get('background_color');
			$color = str_replace('#','',$color["hex"]);
			//$color = str_replace('#','',$properties->__get('background_color'));
			$stringTcPr .='<w:shd w:val="solid" w:color="'.$color.'" />';
		}
		$stringTcPr .= '</w:tcPr>';
		return $stringTcPr;
	}

	private function generateListPr($properties){
		$stringListPr = '<w:pPr><w:pStyle w:val="';
		$stringListPr .= $this->listStyle();
		$stringListPr .= '"/><w:numPr><w:ilvl w:val="';
		$stringListPr .= max((@$this->countTags['ul'] + @$this->countTags['ol'] -1), 0);
		$stringListPr .= '"/><w:numId w:val="';
		$stringListPr .= $this->listType();
		$stringListPr .= '"/></w:numPr>';
		//TODO: write properties
		$stringListPr .= '</w:pPr>';
		return $stringListPr;
	}

	//This function is used to meka sure that all table rows have the same grid
	private function countEmptyColumns($row, $column){
		$counter = 0;
		if(isset(self::$openTable[$row-1][$column]) && self::$openTable[$row-1][$column] > 1){
			array_push(self::$openTable[count(self::$openTable)-1], (self::$openTable[$row-1][$column] -1));
			$counter++;
			$this->countEmptyColumns($row, $column +1);
		}
		return $counter;
	}

}