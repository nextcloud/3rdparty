<?php

/**
 * Create lists
 *
 * @category   Phpdocx
 * @package    elements
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
include_once dirname(__FILE__) . '/CreateElement.inc';

class CreateList extends CreateElement
{
    const MAXDEPTH = 8;

    /**
     *
     * @var mixed
     * @access public
     */
    public $list;
    /**
     *
     * @var array
     * @access public
     */
    public $val;
    /**
     *
     * @var string
     * @access public
     */
    public $font;
    /**
     *
     * @var array
     * @access public
     */
    public $data;
    /**
     * @access private
     * @var CreateList
     * @static
     */
    private static $_instance = NULL;
    /**
     *
     * @access private
     * @var int
     * @static
     */
    private static $_numericList = -1;

    /**
     * Construct
     *
     * @access public
     */
    public function __construct()
    {

    }

    /**
     * Destruct
     *
     * @access public
     */
    public function __destruct()
    {

    }

    /**
     *
     * @access public
     * @return string
     */
    public function __toString()
    {
        $this->cleanTemplate();
        return $this->_xml;
    }

    /**
     *
     * @access public
     * @return CreateList
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreateList();
        }
        return self::$_instance;
    }

    /**
     * Create list
     *
     * @access public
     * @param array args[0]
     * @param array args[1]
     */
    public function createList()
    {
        $this->_xml = '';
        $args = func_get_args();
        $this->list = '';
        if (!isset($args[1]['font'])) {
            $args[1]['font'] = '';
        }

        if ($args[1]['val'] == 2) {
            self::$_numericList++;
            $this->runArray(
                $args[0],
                $args[1]['val'],
                0,//before it was 1: changed
                $args[1]['font']
            );
        } else {
            $this->runArray($args[0], $args[1]['val'], 0, $args[1]['font']);
        }

        $this->_xml = $this->list;
    }

    /**
     * Create embedded list
     *
     * @access public
     */
    public function createEmbeddedList()
    {
        $this->_xml = '__GENERATEP__';
        $this->list = '';
        if ($this->val == 2) {
            self::$_numericList++;
            $this->runArrayEmbedded(
                $this->data,
                $this->val + self::$_numericList,
                1,//before it was 1: changed
                $this->font
            );
        } else {
            $this->runArrayEmbedded($this->data, $this->val, 1, $this->font);
        }

        $this->_xml = $this->list;
    }

    /**
     * Recursive generation of lists styles
     *
     * @access public
     * @param array args[1] Values: array 'bullets' (1 (), 2 (o), 3 ())
     */
    public function createListStyles()
    {
        $this->_xml = '';
        $args = func_get_args();
        $this->list = '';

        $current = $args[0];
        $styleId = $args[1];

        $style = $this->bulletStyle($styleId);
        $indent = $this->bulletIndent($current);

        $this->generateLVL($current);
        $this->generateSTART();
        $this->generateNUMFMT();
        $this->generateLVLTEXT($style['lvlText']);
        $this->generateLVLJC();
        $this->generatePPRS();
        $this->generateIND($indent);
        $this->generateRPRS();
        $this->generateRFONTSTYLE($style['font']);
    }

    /**
     * Init list
     *
     * @access public
     * @param array $args[0]
     */
    public function initList()
    {
        $args = func_get_args();
        $this->val = $args[0][1]['val'];
        $this->font = $args[0][1]['font'];
        $this->data = $args[0][0];
    }

    /**
     * Add list
     *
     * @param string $list
     * @access protected
     */
    protected function addList($list)
    {
        $this->_xml = str_replace('__GENERATER__', $list, $this->_xml);
    }

    /**
     * Generate w:ilfo
     *
     * @param int $val
     * @access protected
     */
    protected function generateILFO($val = 0)
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
            ':ilfo ' . CreateElement::NAMESPACEWORD .
            ':val="' . $val .
            '"></' . CreateElement::NAMESPACEWORD .
            ':ilfo>';
        $this->_xml = str_replace('__GENERATEILFO__', $xml, $this->_xml);
    }

    /**
     * Generate w:ilvl
     *
     * @param string $val
     * @access protected
     */
    protected function generateILVL($val = '')
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
            ':ilvl ' . CreateElement::NAMESPACEWORD .
            ':val="' . $val . '"></' . CreateElement::NAMESPACEWORD .
            ':ilvl>__GENERATEPSTYLE__';
        $this->_xml = str_replace('__GENERATEPSTYLE__', $xml, $this->_xml);
    }

    /**
     * Generate w:ind
     *
     * @access protected
     */
    protected function generateIND($left = '720')
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
                ':ind w:left="' . $left .'" w:hanging="360"/>';

        $this->_xml = str_replace('__GENERATEIND__', $xml, $this->_xml);
    }

    /**
     * Generate w:listpr
     *
     * @access protected
     */
    protected function generateLISTPR()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
            ':listPr>__GENERATEILVL____GENERATEILFO__</' .
            CreateElement::NAMESPACEWORD . ':listPr>__GENERATER__';
        $this->_xml = str_replace('__GENERATER__', $xml, $this->_xml);
    }

    /**
     * Generate w:lvl
     *
     * @access protected
     */
    protected function generateLVL($current)
    {
        $this->_xml = '<' . CreateElement::NAMESPACEWORD . ':lvl
                w:ilvl="' . $current . '" w:tplc="0C0A0001">__GENERATESTART__</' .
                CreateElement::NAMESPACEWORD . ':lvl>';
    }

    /**
     * Generate w:lvlJc
     *
     * @access protected
     */
    protected function generateLVLJC()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
                ':lvlJc w:val="left"/>__generatePPRS__';

        $this->_xml = str_replace('__GENERATELVLJC__', $xml, $this->_xml);
    }

    /**
     * Generate w:lvlText
     *
     * @access protected
     */
    protected function generateLVLTEXT($bullet = '')
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
                ':lvlText w:val="' . $bullet . '"/>__GENERATELVLJC__';

        $this->_xml = str_replace('__GENERATELVLTEXT__', $xml, $this->_xml);
    }

    /**
     * Generate w:numFmt
     *
     * @access protected
     */
    protected function generateNUMFMT()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD . ':numFmt ' .
                CreateElement::NAMESPACEWORD .
                ':val="bullet"/>__GENERATELVLTEXT__';

        $this->_xml = str_replace('__GENERATENUMFMT__', $xml, $this->_xml);
    }

    /**
     * Generate w:numid
     *
     * @param int $val
     * @access protected
     */
    protected function generateNUMID($val)
    {
        if($val == 2){
            $val =CreateDocx::$numOL;
        }else if ($val === 0){
            $val = '';
        }else if ($val == 1){
            $val =CreateDocx::$numUL;
        }

        $xml = '<' . CreateElement::NAMESPACEWORD .
            ':numId ' . CreateElement::NAMESPACEWORD .
            ':val="' . $val . '"></' . CreateElement::NAMESPACEWORD .
            ':numId>';
        $this->_xml = str_replace('__GENERATEPSTYLE__', $xml, $this->_xml);
    }

    /**
     * Generate w:numpr
     *
     * @access protected
     */
    protected function generateNUMPR()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
            ':numPr>__GENERATEPSTYLE__</' . CreateElement::NAMESPACEWORD .
            ':numPr>';
        $this->_xml = str_replace('__GENERATEPSTYLE__', $xml, $this->_xml);
    }

    /**
     * Generate w:ppr
     *
     * @access protected
     */
    protected function generatePPRS()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD . ':pPr>__GENERATEIND__</' .
                CreateElement::NAMESPACEWORD . ':pPr>__GENERATRPR__';

        $this->_xml = str_replace('__generatePPRS__', $xml, $this->_xml);
    }

    /**
     * Generate w:pstyle
     *
     * @param string $val
     * @access protected
     */
    protected function generatePSTYLE($val)
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
            ':pStyle ' . CreateElement::NAMESPACEWORD . ':val="' . $val .
            '"/>__GENERATEPSTYLE__';
        $this->_xml = str_replace('__GENERATEPPR__', $xml, $this->_xml);
    }

    /**
     * Generate w:rfonts
     *
     * @param string $font
     * @access protected
     */
    protected function generateRFONTSTYLE($font = 'Symbol')
    {
        $xml = '<' . CreateElement::NAMESPACEWORD .
                ':rFonts ' . CreateElement::NAMESPACEWORD .
                ':ascii="' . $font . '" ' . CreateElement::NAMESPACEWORD .
                ':hAnsi="' . $font . '" ' . CreateElement::NAMESPACEWORD .
                ':hint="default"/>';

        $this->_xml = str_replace('__GENERATERFONTS__', $xml, $this->_xml);
    }

    /**
     * Generate w:rpr
     *
     * @access protected
     */
    protected function generateRPRS()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD . ':rPr>__GENERATERFONTS__</' .
                CreateElement::NAMESPACEWORD . ':rPr>';

        $this->_xml = str_replace('__GENERATRPR__', $xml, $this->_xml);
    }

    /**
     * Recursive generation of lists
     *
     * @param array $dat
     * @param string $val
     * @param int $depth
     * @param string $font
     * @access protected
     */
    protected function runArray($dat, $val, $depth, $font = '')
    {
        foreach ($dat as $cont) {
            $this->generateP();
            $this->generatePPR();
            $this->generatePSTYLE('ListParagraphPHPDOCX');
            $this->generateNUMPR();
            //$this->generateLISTPR();
            $this->generateILFO();
            $this->generateILVL($depth);
            $this->generateNUMID($val);
            if ($cont instanceof CreateLink) {
                $cont->createEmbeddedLink(
                    $cont->getTitle(),
                    $cont->getLink()
                );
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof CreateImage) {
                $cont->createEmbeddedImage('List');
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif (is_object($cont) && strpos(get_class($cont), 'Chart') !== false) {
                $cont->createEmbeddedGraphic();
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof CreateTextBox) {
                $cont->createEmbeddedTextBox();
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof CreateText) {
                $cont->createEmbeddedText($cont);
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof WordML) {
                $runContent = $cont->inlineWordML();
                $this->addList((string) $runContent);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof WordMLFragment) {
                $runContent = $cont->inlineWordML();
                $this->addList((string) $runContent);
                $this->list .= $this->_xml;
            }else {
                $this->generateR();
                if (isset($font)) {
                    $this->generateRPR();
                    $this->generateRFONTS($font);
                }
                $this->generateT($cont);
                $this->list .= $this->_xml;
            }
        }
    }

    /**
     * Recursive generation of embedded lists
     *
     * @param array $dat
     * @param string $val
     * @param int $depth
     */
    protected function runArrayEmbedded($dat, $val, $depth)
    {
        foreach ($dat as $cont) {
            $this->generateP();
            $this->generatePPR();
            $this->generatePSTYLE('ListParagraphPHPDOCX');
            $this->generateNUMPR();
            //$this->generateLISTPR();
            $this->generateILFO();
            $this->generateILVL($depth);
            $this->generateNUMID($val);
            if ($cont instanceof CreateLink) {
                $cont->createEmbeddedLink(
                    $cont->getTitle(),
                    $cont->getLink(),
                    $cont->getFont()
                );
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof CreateImage) {
                $cont->createEmbeddedImage('List');
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif (strpos(get_class($cont), 'Chart') !== false) {
                $cont->createEmbeddedGraphic();
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof CreateTextBox) {
                $cont->createEmbeddedTextBox();
                $this->addList((string) $cont);
                $this->list .= $this->_xml;
            } elseif ($cont instanceof WordML) {
                $runContent = $cont->inlineWordML();
                $this->addList((string) $runContent);
                $this->list .= $this->_xml;
            } else {
                $this->generateR();
                if (isset($this->font)) {
                    $this->generateRPR();
                    $this->generateRFONTS($this->font);
                }
                $this->generateT($cont);
                $this->list .= $this->_xml;
            }
        }
    }

    /**
     * Generate w:start
     *
     * @access protected
     */
    protected function generateSTART()
    {
        $xml = '<' . CreateElement::NAMESPACEWORD . ':start ' .
                CreateElement::NAMESPACEWORD . ':val="1"/>__GENERATENUMFMT__';

        $this->_xml = str_replace('__GENERATESTART__', $xml, $this->_xml);
    }

    /**
     * Prefefined indent
     *
     * @param int $id
     */
    private function bulletIndent($i)
    {
        $output = array();
        switch ($i) {
            case 0:
                $indent = 720;
            break;
            case 1:
                $indent = 1440;
            break;
            case 2:
                $indent = 2160;
            break;
            case 3:
                $indent = 2880;
            break;
            case 4:
                $indent = 3600;
            break;
            case 5:
                $indent = 4320;
            break;
            case 6:
                $indent = 5040;
            break;
            case 7:
                $indent = 5760;
            break;
            case 8:
                $indent = 6480;
            break;
            default:
                $indent = 720;
            break;
        }
        return $indent;
    }

    /**
     * Predefined bullets
     *
     * @param int $id
     */
    private function bulletStyle($id)
    {
        $output = array();
        switch ($id) {
            case 1:
                $output['lvlText'] = '';
                $output['font'] = 'Symbol';
            break;
            case 2:
                $output['lvlText'] = 'o';
                $output['font'] = 'Courier New';
            break;
            case 3:
                $output['lvlText'] = '';
                $output['font'] = 'Wingdings';
            break;
            default:
                $output['lvlText'] = '';
                $output['font'] = 'Symbol';
            break;
        }
        return $output;
    }

}
