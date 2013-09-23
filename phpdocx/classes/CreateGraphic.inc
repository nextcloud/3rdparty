<?php

/**
 * Create graphics(charts)
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

class CreateGraphic extends CreateElement
{
	const NAMESPACEWORD = 'c';

    /**
     *
     * @access protected
     * @var string
     */
    protected $_xmlChart;

    /**
     *
     * @access protected
     * @var string
     */
    protected static $_rId;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_textalign;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_jc;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_sizeX;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_sizeY;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_type;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_showPercent;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_showCategory;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_showValue;

    /**
     *
     * @access protected
     * @var <type>
     */
    protected $_data;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_rotX;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_rotY;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_perspective;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_color;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_float;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_groupBar;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_horizontalOffset;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_title;

    /**
     *
     * @access protected
     * @var string
     */
    protected $_name;

    /**
     * @access protected
     * @var string
     */
    protected $_font;

    /**
     * @access protected
     * @var string
     */
    protected $_legendPos;

    /**
     * @access protected
     * @var string
     */
    protected $_legendOverlay;

    /**
     * @access protected
     * @var string
     */
    protected $_border;

    /**
     * @access protected
     * @var string
     */
    protected $_haxLabel;

    /**
     * @access protected
     * @var string
     */
    protected $_vaxLabel;

    /**
     * @access protected
     * @var string
     */
    protected $_haxLabelDisplay;

    /**
     * @access protected
     * @var string
     */
    protected $_vaxLabelDisplay;

    /**
     * @access protected
     * @var string
     */
    protected $_showtable;

    /**
     * @access protected
     * @var string
     */
    protected $_hgrid;

    /**
     * @access protected
     * @var string
     */
    protected $_vgrid;


    /**
     * @access protected
     * @var string
     */
    protected $_explosion;

    /**
     * @access protected
     * @var string
     */
    protected $_holeSize;

    /**
     * @access protected
     * @var string
     */
    protected $_symbol;

    /**
     * @access protected
     * @var string
     */
    protected $_symbolSize;

    /**
     * @access protected
     * @var string
     */
    protected $_style;

    /**
     * @access protected
     * @var boolean
     */
    protected $_smooth;

    /**
     *
     * @access protected
     * @var int
     */
    protected $_verticalOffset;

    /**
     * @access protected
     * @var boolean
     */
    protected $_wireframe;

    /**
     * @access protected
     * @var CreateGraphic
     * @static
     */
    protected static $_instance = null;


    /**
     * Construct
     *
     * @access public
     */

    public function __construct()
    {
        $this->_rId = '';
        $this->_textalign = '';
        $this->_jc = '';
        $this->_sizeX = '';
        $this->_sizeY = '';
        $this->_type = '';
        $this->_data = '';
        $this->_rotX = '';
        $this->_rotY = '';
        $this->_perspective = '';
        $this->_color = '';
        $this->_groupBar = '';
        $this->_title = '';
        $this->_font = '';
        $this->_xml = '';
        $this->_name = '';
        $this->_legendPos = '';
        $this->_legendOverlay = '';
        $this->_border = '';
        $this->_haxLabel = '';
        $this->_vaxLabel = '';
        $this->_haxLabelDisplay = '';
        $this->_vaxLabelDisplay = '';
        $this->_showtable = '';
        $this->_hgrid = '';
        $this->_vgrid = '';

        $this->_gapWidth = '';
        $this->_secondPieSize = '';
        $this->_splitType = '';
        $this->_splitPos = '';
        $this->_custSplit = '';
        $this->_subtype = '';

        $this->_explosion = '';
        $this->_holeSize = '';
        $this->_symbol = '';
        $this->_symbolSize = '';
        $this->_style = '';
        $this->_smooth = false;
        $this->_wireframe = false;

        $this->_showPercent = '';
        $this->_showValue = false;
        $this->_showCategory = false;
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
     * @return CreateGraphic
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreatePieChart();
        }
        return self::$_instance;
    }

    /**
     *
     * @access public
     * @return string
     */
    public function __toString()
    {
        return $this->_xml;
    }

    /**
     * Setter. Rid
     *
     * @access public
     * @param string $rId
     */
    public function setRId($rId)
    {
        $this->_rId = $rId;
    }

    /**
     * Getter. Rid
     *
     * @access public
     * @return string
     */
    public function getRId()
    {
        return $this->_rId;
    }

    /**
     * Setter. Name
     *
     * @access public
     * @param string $name
     */
    public function setName($name)
    {
        $this->_name = $name;
    }

    /**
     * Getter. Name
     *
     * @access public
     * @return string
     */
    public function getName()
    {
        return $this->_name;
    }

    /**
     * Setter. Xml chart
     *
     * @access public
     * @param string $xmlChart
     */
    public function setXmlChart($xmlChart)
    {
        $this->_xmlChart = $xmlChart;
    }

    /**
     * Getter. Xml chart
     *
     * @access public
     * @return string
     */
    public function getXmlChart()
    {
        return $this->_xmlChart;
    }

    /**
     * Create embedded graphic
     *
     * @access public
     * @param array $args[0]
     * @param array $args[1]
     * @return boolean
     */
    public function createEmbeddedGraphic()
    {
        $this->_xmlChart = '';
        if ($this->_type != '') {
            $this->createEmbeddedDocumentXml();
            return true;
        } else {
            echo 'You haven`t added a chart type';
            return false;
        }
    }

    /**
     * Create graphic
     *
     * @access public
     * @param array $args[0]
     * @param array $args[1]
     * @return boolean
     */
    public function CreateGraphic()
    {
        $this->_xmlChart = '';
        $args = func_get_args();
        $this->setRId($args[0]);
        $this->initGraphic($args[1]);
        if (isset($this->_type) && isset($args[0])) {
            if ($this->createEmbeddedXmlChart() == false) {
                echo 'You haven`t added legends';
                return false;
            }
            $this->createDOCUEMNTXML();
            return true;
        } else {
            echo 'You haven`t added a chart type';
            return false;
        }
    }

    /**
     * Init graphic
     *
     * @access public
     * @param array $args[0]
     */
    public function initGraphic()
    {
        $args = func_get_args();
        $this->_type = $args[0]['type'];
        $this->values = $args[0]['data'];
        if(isset($args[0]['float']))
            $this->_float = $args[0]['float'];
        if(isset($args[0]['horizontalOffset']))
            $this->_horizontalOffset = $args[0]['horizontalOffset'];
        if(isset($args[0]['verticalOffset']))
            $this->_verticalOffset = $args[0]['verticalOffset'];
        if(isset($args[0]['textWrap']))
            $this->_textalign = $args[0]['textWrap'];
        if(isset($args[0]['jc']))
            $this->_jc = $args[0]['jc'];
        if(isset($args[0]['sizeX']))
            $this->_sizeX = $args[0]['sizeX'];
        if(isset($args[0]['sizeY']))
            $this->_sizeY = $args[0]['sizeY'];
        if(isset($args[0]['showPercent']))
            $this->_showPercent = $args[0]['showPercent'];
        if(isset($args[0]['showValue']))
            $this->_showValue = $args[0]['showValue'];
        if(isset($args[0]['showCategory']))
            $this->_showCategory = $args[0]['showCategory'];
        if(isset($args[0]['rotX']))
            $this->_rotX = $args[0]['rotX'];
        if(isset($args[0]['rotY']))
            $this->_rotY = $args[0]['rotY'];
        if(isset($args[0]['perspective']))
            $this->_perspective = $args[0]['perspective'];
        if(isset($args[0]['color']))
            $this->_color = $args[0]['color'];
        if(isset($args[0]['groupBar']))
            $this->_groupBar = $args[0]['groupBar'];
        if(isset($args[0]['title']))
            $this->_title = $args[0]['title'];
        if(isset($args[0]['font']))
            $this->_font = $args[0]['font'];
        if(isset($args[0]['legendPos']))
            $this->_legendPos = $args[0]['legendPos'];
        if(isset($args[0]['legendOverlay']))
            $this->_legendOverlay = $args[0]['legendOverlay'];
        if(isset($args[0]['border']))
            $this->_border = $args[0]['border'];
        if(isset($args[0]['haxLabel']))
            $this->_haxLabel = $args[0]['haxLabel'];
        if(isset($args[0]['vaxLabel']))
            $this->_vaxLabel = $args[0]['vaxLabel'];
        if(isset($args[0]['haxLabelDisplay']))
            $this->_haxLabelDisplay = $args[0]['haxLabelDisplay'];
        if(isset($args[0]['vaxLabelDisplay']))
            $this->_vaxLabelDisplay = $args[0]['vaxLabelDisplay'];
        if(isset($args[0]['showtable']))
            $this->_showtable = $args[0]['showtable'];
        if(isset($args[0]['hgrid']))
            $this->_hgrid = $args[0]['hgrid'];
        if(isset($args[0]['vgrid']))
            $this->_vgrid = $args[0]['vgrid'];
        if(isset($args[0]['style']))
            $this->_style = $args[0]['style'];
        if(isset($args[0]['gapWidth']))
            $this->_gapWidth = $args[0]['gapWidth'];
        if(isset($args[0]['secondPieSize']))
            $this->_secondPieSize = $args[0]['secondPieSize'];
        if(isset($args[0]['splitType']))
            $this->_splitType = $args[0]['splitType'];
        if(isset($args[0]['splitPos']))
            $this->_splitPos = $args[0]['splitPos'];
        if(isset($args[0]['custSplit']))
            $this->_custSplit = $args[0]['custSplit'];
        if(isset($args[0]['subtype']))
            $this->_subtype = $args[0]['subtype'];
        if(isset($args[0]['explosion']))
            $this->_explosion = $args[0]['explosion'];
        if(isset($args[0]['holeSize']))
            $this->_holeSize = $args[0]['holeSize'];
        if(isset($args[0]['symbol']))
            $this->_symbol = $args[0]['symbol'];
        if(isset($args[0]['symbolSize']))
            $this->_symbolSize = $args[0]['symbolSize'];
        if(isset($args[0]['smooth']))
            $this->_smooth = $args[0]['smooth'];
        if(isset($args[0]['wireframe']))
            $this->_wireframe = $args[0]['wireframe'];
    }



    /**
     * Create embedded document xml
     *
     * @access protected
     * @return array $args
     */
    protected function createEmbeddedDocumentXml()
    {
        $args = func_get_args();
        if ($this->_textalign != '' &&
            ($this->_textalign < 0 || $this->_textalign > 5)
        ) {
            $textalign = 0;
        } else {
            $textalign = $this->_textalign;
        }
        if ($this->_sizeX != '') {
            $sizeX = $this->_sizeX * CreateImage::CONSTWORD;
        } else {
            $sizeX = 2993296;
        }
        if ($this->_sizeY != '') {
            $sizeY = $this->_sizeY * CreateImage::CONSTWORD;
        } else {
            $sizeY = 2238233;
        }

        $this->_xml = '';
        $this->generateQUITAR();
        $this->generateRPR();
        $this->generateNOPROOF();
        $this->generateDRAWING();
        if ($textalign == 0) {
            $this->generateINLINE();
        } else {
            if ($textalign == 3) {
                $this->generateANCHOR(1);
            } else {
                $this->generateANCHOR();
            }
            $this->generateSIMPLEPOS();
            $this->generatePOSITIONH();
            if (isset($this->_float) && ($this->_float == 'left' || $this->_float == 'right' || $this->_float == 'center')) {
                $this->generateALIGN($this->_float);
            }
            if (isset($this->_horizontalOffset) && is_numeric($this->_horizontalOffset)) {
                $this->generatePOSOFFSET($this->_horizontalOffset);
            }else{
                $this->generatePOSOFFSET(0);
            }
            $this->generatePOSITIONV();
            if (isset($this->_verticalOffset) && is_numeric($this->_verticalOffset)) {
                $this->generatePOSOFFSET($this->_verticalOffset);
            }else{
               $this->generatePOSOFFSET(0);
            }
        }

        $this->generateEXTENT($sizeX, $sizeY);
        $this->generateEFFECTEXTENT();
        switch ($textalign) {
            case 1:
                $this->generateWRAPSQUARE();
                break;
            case 2:
            case 3:
                $this->generateWRAPNONE();
                break;
            case 4:
                $this->generateWRAPTOPANDBOTTOM();
                break;
            case 5:
                $this->generateWRAPTHROUGH();
                $this->generateWRAPPOLYGON();
                $this->generateSTART();
                $this->generateLINETO();
                $this->generateLINETO('21540', '21342');
                $this->generateLINETO('21540', '0');
                $this->generateLINETO('-198', '0');
                break;
            default:
                break;
        }
        $this->generateDOCPR($this->getRId());
        $this->generateCNVGRAPHICFRAMEPR();
        $this->generateGRAPHIC();
        $this->generateGRAPHICDATA(
            'http://schemas.openxmlformats.org/'.
            'drawingml/2006/chart'
        );
        $this->generateDOCUMENTCHART();
        $this->cleanTemplate();
        return true;
    }



    /**
     * return the transposed matrix
     *
     * @access public
     * @param array
     */
    public function transposed($matrix){
        $data = array();
        foreach ($matrix as $key => $value) {
            foreach ($value as $key2 => $value2) {
                $data[$key2][$key] = $value2;
            }
        }
        return $data;
    }

    /**
     * return the array with just 1 deep
     *
     * @access public
     * @param array
     */
    public function linear($matrix){
        $data = array();
        foreach($matrix as $key => $value){
            foreach($value as $ind => $val){
                $data[] = $val;
            }
        }
        return $data;
    }

    /**
     * return the array of data prepared to modify the chart data
     *
     * @access public
     * @param array
     */
    public function prepareData($data){
        $newData = array();
        $simple = true;
        if(isset($data['legend']))
            unset($data['legend']);
        foreach($data as $dat){
            if(count($dat) > 1)
               $simple = false;
           break;
        }
        foreach($data as $dat){
            if($simple)
                $newData[] = $dat[0];
            else
                $newData[] = $dat;
        }
        if($simple)
            return $this->linear(array($newData));
        else
            return $this->linear($this->transposed($newData));
    }

    /**
     * Create document xml
     *
     * @access protected
     * @param array $args[0]
     */
    protected function createDOCUEMNTXML()
    {
        if (empty($this->_textalign) ||
            $this->_textalign < 0 ||
            $this->_textalign > 5)
            $textalign = 0;
        else {
            $textalign = $this->_textalign;
        }
        if (!empty($this->_sizeX))
            $sizeX = $this->_sizeX * CreateImage::CONSTWORD;
        else {
            $sizeX = 2993296;
        }
        if (!empty($this->_sizeY))
            $sizeY = $this->_sizeY * CreateImage::CONSTWORD;
        else {
            $sizeY = 2238233;
        }


        $this->_xml = '';
        $this->generateP();
        if (!empty($this->_jc)) {
            $this->generatePPR();
            $this->generateJC($this->_jc);
        }
        $this->generateR();
        $this->generateRPR();
        $this->generateNOPROOF();
        $this->generateDRAWING();
        if ($textalign == 0) {
            $this->generateINLINE();
        } else {
            if ($textalign == 3) {
                $this->generateANCHOR(1);
            } else {
                $this->generateANCHOR();
            }
            $this->generateSIMPLEPOS();
            $this->generatePOSITIONH();
            if (isset($this->_float) && ($this->_float == 'left' || $this->_float == 'right' || $this->_float == 'center')) {
                $this->generateALIGN($this->_float);
            }
            if (isset($this->_horizontalOffset) && is_numeric($this->_horizontalOffset)) {
                $this->generatePOSOFFSET($this->_horizontalOffset);
            }else{
                $this->generatePOSOFFSET(0);
            }
            $this->generatePOSITIONV();
            if (isset($this->_verticalOffset) && is_numeric($this->_verticalOffset)) {
                $this->generatePOSOFFSET($this->_verticalOffset);
            }else{
               $this->generatePOSOFFSET(0);
            }
        }

        $this->generateEXTENT($sizeX, $sizeY);
        $this->generateEFFECTEXTENT();
        switch ($textalign) {
            case 1:
                $this->generateWRAPSQUARE();
                break;
            case 2:
            case 3:
                $this->generateWRAPNONE();
                break;
            case 4:
                $this->generateWRAPTOPANDBOTTOM();
                break;
            case 5:
                $this->generateWRAPTHROUGH();
                $this->generateWRAPPOLYGON();
                $this->generateSTART();
                $this->generateLINETO();
                $this->generateLINETO('21540', '21342');
                $this->generateLINETO('21540', '0');
                $this->generateLINETO('-198', '0');
                break;
            default:
                break;
        }
        $this->generateDOCPR($this->getRId());
        $this->generateCNVGRAPHICFRAMEPR();
        $this->generateGRAPHIC();
        $this->generateGRAPHICDATA(
            'http://schemas.openxmlformats.org/'.
            'drawingml/2006/chart'
        );
        $this->generateDOCUMENTCHART();
        $this->cleanTemplate();
        return true;
    }

    /**
     * Generate w:autotitledeleted
     *
     * @access protected
     * @param string $val
     */
    protected function generateAUTOTITLEDELETED($val = '1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':autoTitleDeleted val="' . $val .
            '"></' . CreateGraphic::NAMESPACEWORD .
            ':autoTitleDeleted>__GENERATECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:barChart
     *
     * @access protected
     */
    protected function generateBARCHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':barChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':barChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:barDir
     *
     * @access protected
     * @param string $val
     */
    protected function generateBARDIR($val = 'bar')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':barDir val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':barDir>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:bodypr
     *
     * @access protected
     */
    protected function generateBODYPR()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':bodyPr></' .
            CreateImage::NAMESPACEWORD1 . ':bodyPr>__GENERATERICH__';
        $this->_xmlChart = str_replace(
            '__GENERATERICH__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:chart
     *
     * @access protected
     */
    protected function generateCHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':chart>__GENERATECHART__</' . CreateGraphic::NAMESPACEWORD .
            ':chart>__GENERATECHARTSPACE__';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate chartspace XML
     *
     * @access protected
     */
    protected function generateCHARTSPACE()
    {
        $this->_xmlChart = '<?xml version="1.0" encoding="UTF-8" ' .
            'standalone="yes" ?><' . CreateGraphic::NAMESPACEWORD .
            ':chartSpace xmlns:c="http://schemas.openxmlformats.o' .
            'rg/drawingml/2006/chart" xmlns:a="http://schemas.open' .
            'xmlformats.org/drawingml/2006/main" xmlns:r="http://s' .
            'chemas.openxmlformats.org/officeDocument/2006/relatio' .
            'nships">__GENERATECHARTSPACE__</' .
            CreateGraphic::NAMESPACEWORD . ':chartSpace>';
    }

    /**
     * Generate w:date1904
     *
     * @access protected
     * @param string $val
     */
    protected function generateDATE1904($val = '1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':date1904 val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':date1904>__GENERATECHARTSPACE__';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__',
            $xml,
            $this->_xmlChart
        );
    }

    /**
     * Generate w:defrpr
     *
     * @access protected
     */
    protected function generateDEFRPR()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 .
            ':defRPr>__GENERATEDEFRPR__</' . CreateImage::NAMESPACEWORD1 .
            ':defRPr>__GENERATETITLEPPR__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLEPPR__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:lang
     *
     * @access protected
     * @param string $val
     */
    protected function generateLANG($val = 'es-ES')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':lang val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':lang>__GENERATECHARTSPACE__';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__',
            $xml,
            $this->_xmlChart
        );
    }

    /**
     * Generate w:lineChart
     *
     * @access protected
     */
    protected function generateLINECHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':lineChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':lineChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:areaChart
     *
     * @access protected
     */
    protected function generateAREACHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':areaChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':areaChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:piechart
     *
     * @access protected
     */
    protected function generatePIECHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':pieChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':pieChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:surfaceChart
     *
     * @access protected
     */
    protected function generateSURFACECHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':surfaceChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':surfaceChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:wireframe
     *
     * @access protected
     */
    protected function generateWIREFRAME($val = 1)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':wireframe val="' . $val . '" />__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:bubbleChart
     *
     * @access protected
     */
    protected function generateBUBBLECHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':bubbleChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':bubbleChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:plotarea
     *
     * @access protected
     */
    protected function generatePLOTAREA()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':plotArea>__GENERATEPLOTAREA__</' . CreateGraphic::NAMESPACEWORD .
            ':plotArea>__GENERATECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:radarChart
     *
     * @access protected
     */
    protected function generateRADARCHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':radarChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':radarChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:radarChart
     *
     * @access protected
     */
    protected function generateRADARCHARTSTYLE($style = 'radar')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':radarStyle val="' . $style . '" />__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:rich
     *
     * @access protected
     */
    protected function generateRICH()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':rich>__GENERATERICH__</' . CreateGraphic::NAMESPACEWORD .
            ':rich>__GENERATETITLETX__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLETX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:style
     *
     * @access protected
     * @param string $val
     */
    protected function generateSTYLE($val = '2')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':style val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':style>__GENERATECHARTSPACE__';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__',
            $xml,
            $this->_xmlChart
        );
    }

    /**
     * Generate w:title
     *
     * @access protected
     */
    protected function generateTITLE()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':title>__GENERATETITLE__</' . CreateGraphic::NAMESPACEWORD .
            ':title>__GENERATECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:layout
     *
     * @access protected
     */
    protected function generateLAYOUT()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':layout></' . CreateGraphic::NAMESPACEWORD .
            ':layout>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }


    /**
     * Generate w:titlelayout
     *
     * @access protected
     * @param string $nombre
     */
    protected function generateTITLELAYOUT($nombre = '')
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 .
            ':layout></' . CreateImage::NAMESPACEWORD1 .
            ':layout>';
        $this->_xmlChart = str_replace(
            '__GENERATETITLE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titlep
     *
     * @access protected
     */
    protected function generateTITLEP()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 .
            ':p>__GENERATETITLEP__</' . CreateImage::NAMESPACEWORD1 .
            ':p>__GENERATERICH__';
        $this->_xmlChart = str_replace(
            '__GENERATERICH__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titleppr
     *
     * @access protected
     */
    protected function generateTITLEPPR()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 .
            ':pPr>__GENERATETITLEPPR__</' . CreateImage::NAMESPACEWORD1 .
            ':pPr>__GENERATETITLEP__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLEP__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titler
     *
     * @access protected
     */
    protected function generateTITLER()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 .
            ':r>__GENERATETITLER__</' . CreateImage::NAMESPACEWORD1 .
            ':r>__GENERATETITLEP__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLEP__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titlerfonts
     *
     * @access protected
     * @param string $font
     */
    protected function generateTITLERFONTS($font = '')
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':latin typeface="' .
            $font . '" pitchFamily="34" charset="0"></' .
            CreateImage::NAMESPACEWORD1 . ':latin ><' .
            CreateImage::NAMESPACEWORD1 .
            ':cs typeface="' . $font . '" pitchFamily="34" charset="0"></' .
            CreateImage::NAMESPACEWORD1 . ':cs>';
        $this->_xmlChart = str_replace(
            '__GENERATETITLERPR__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titlerpr
     *
     * @access protected
     */
    protected function generateTITLERPR($lang = 'es-ES')
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':rPr lang="' .
            $lang . '">__GENERATETITLERPR__</' . CreateImage::NAMESPACEWORD1 .
            ':rPr>__GENERATETITLER__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titlet
     *
     * @access protected
     * @param string $nombre
     */
    protected function generateTITLET($nombre = '')
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':t>' .
            $nombre . '</' . CreateImage::NAMESPACEWORD1 .
            ':t>__GENERATETITLER__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:titletx
     *
     * @access protected
     */
    protected function generateTITLETX()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':tx>__GENERATETITLETX__</' . CreateGraphic::NAMESPACEWORD .
            ':tx>__GENERATETITLE__';
        $this->_xmlChart = str_replace(
            '__GENERATETITLE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:varyColors
     *
     * @access protected
     * @param string $val
     */
    protected function generateVARYCOLORS($val = '1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':varyColors val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':varyColors>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:grouping
     *
     * @access protected
     * @param string $val
     */
    protected function generateGROUPING($val = 'stacked')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':grouping val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':grouping>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:ser
     *
     * @access protected
     */
    protected function generateSER()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':ser>__GENERATESER__</' . CreateGraphic::NAMESPACEWORD .
            ':ser>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:idx
     *
     * @access protected
     * @param string $val
     */
    protected function generateIDX($val = '0')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':idx val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':idx>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:order
     *
     * @access protected
     * @param string $val
     */
    protected function generateORDER($val = '0')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':order val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':order>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:tx
     *
     * @access protected
     */
    protected function generateTX()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':tx>__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':tx>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:dLbls
     *
     * @access protected
     */
    protected function generateSERDLBLS()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':dLbls>__GENERATEDLBLS__</' . CreateGraphic::NAMESPACEWORD .
            ':dLbls>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:showVal
     *
     * @access protected
     */
    protected function generateSHOWVAL($val = 1)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':showVal val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':showVal>__GENERATEDLBLS__';
        $this->_xmlChart = str_replace(
            '__GENERATEDLBLS__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:showCatName
     *
     * @access protected
     */
    protected function generateSHOWCATNAME($val = 1)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':showCatName val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':showCatName>__GENERATEDLBLS__';
        $this->_xmlChart = str_replace(
            '__GENERATEDLBLS__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:strref
     *
     * @access protected
     */
    protected function generateSTRREF()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':strRef>__GENERATESTRREF__</' . CreateGraphic::NAMESPACEWORD .
            ':strRef>__GENERATETX__';
        $this->_xmlChart = str_replace(
            '__GENERATETX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:f
     *
     * @access protected
     * @param string $val
     */
    protected function generateF($val = 'Sheet1!$B$1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':f>' .
            $val . '</' . CreateGraphic::NAMESPACEWORD .
            ':f>__GENERATESTRREF__';
        $this->_xmlChart = str_replace(
            '__GENERATESTRREF__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:strcache
     *
     * @access protected
     */
    protected function generateSTRCACHE()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':strCache>__GENERATESTRCACHE__</' . CreateGraphic::NAMESPACEWORD .
            ':strCache>__GENERATESTRREF__';
        $this->_xmlChart = str_replace(
            '__GENERATESTRREF__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:ptcount
     *
     * @access protected
     * @param string $val
     */
    protected function generatePTCOUNT($val = '1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':ptCount val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':ptCount>__GENERATESTRCACHE__';
        $this->_xmlChart = str_replace(
            '__GENERATESTRCACHE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:pt
     *
     * @access protected
     * @param string $idx
     */
    protected function generatePT($idx = '0')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':pt idx="' .
            $idx . '">__GENERATEPT__</' . CreateGraphic::NAMESPACEWORD .
            ':pt>__GENERATESTRCACHE__';
        $this->_xmlChart = str_replace(
            '__GENERATESTRCACHE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:v
     *
     * @access protected
     * @param string $idx
     */
    protected function generateV($idx = 'Ventas')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':v>' .
            $idx . '</' . CreateGraphic::NAMESPACEWORD . ':v>';
        $this->_xmlChart = str_replace(
            '__GENERATEPT__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:cat
     *
     * @access protected
     */
    protected function generateCAT()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':cat>__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':cat>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:val
     *
     * @access protected
     */
    protected function generateVAL()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':val>__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':val>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:numcache
     *
     * @access protected
     */
    protected function generateNUMCACHE()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':numCache>__GENERATESTRCACHE__</' .
            CreateGraphic::NAMESPACEWORD . ':numCache>__GENERATESTRREF__';
        $this->_xmlChart = str_replace(
            '__GENERATESTRREF__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:layout
     *
     * @access protected
     * @param string $font
     */

    protected function generateLEGENDLAYOUT()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':layout />__GENERATELEGEND__';
        $this->_xmlChart = str_replace(
            '__GENERATELEGEND__', $xml, $this->_xmlChart
        );
    }
    /**
     * Generate w:xVal
     *
     * @access protected
     */
    protected function generateXVAL()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':xVal>__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':xVal>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }



    /**
     * Generate w:spPr
     *
     * @access protected
     */
    protected function generateSPPR_SER()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':spPr>__GENERATESPPR__</' . CreateGraphic::NAMESPACEWORD .
            ':spPr>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:yVal
     *
     * @access protected
     */
    protected function generateYVAL()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':yVal>__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':yVal>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }


    /**
     * Generate w:bubbleSize
     *
     * @access protected
     */
    protected function generateBUBBLESIZE()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':bubbleSize>__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':bubbleSize>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }


    /**
     * Generate w:smooth
     *
     * @access protected
     */
    protected function generateSMOOTH($val=1)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':smooth val="' . $val . '">__GENERATETX__</' . CreateGraphic::NAMESPACEWORD .
            ':smooth>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }


    /**
     * Generate w:bubbleScale
     *
     * @access protected
     */
    protected function generateBUBBLESCALE($val = 100)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':bubbleScale val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':bubbleScale>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate a:txPr
     *
     * @access protected
     * @param string $font
     */
    protected function generateTXPR()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':txPr>__GENERATETXPR__</' . CreateGraphic::NAMESPACEWORD . ':txPr>__GENERATECHARTSPACE__';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:bodyPr
     *
     * @access protected
     */
    protected function generateLEGENDBODYPR()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':bodyPr></' . CreateImage::NAMESPACEWORD1 . ':bodyPr>__GENERATERICH__';
        $this->_xmlChart = str_replace(
            '__GENERATETXPR__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:lststyle
     *
     * @access protected
     */
    protected function generateLSTSTYLE()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 .
            ':lstStyle></' . CreateImage::NAMESPACEWORD1 .
            ':lstStyle>__GENERATERICH__';
        $this->_xmlChart = str_replace(
            '__GENERATERICH__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate a:p
     *
     * @access protected
     */
    protected function generateAP()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':p>__GENERATEAP__</' . CreateImage::NAMESPACEWORD1 . ':p>__GENERATERICH__';
        $this->_xmlChart = str_replace(
            '__GENERATERICH__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate a:pPr
     *
     * @access protected
     */
    protected function generateAPPR($rtl = 0)
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':pPr rtl="'. $rtl . '">__GENERATETITLEPPR__</' . CreateImage::NAMESPACEWORD1 . ':pPr>__GENERATEAP__';
        $this->_xmlChart = str_replace(
            '__GENERATEAP__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate a:endParaRPr
     *
     * @access protected
     */
    protected function generateENDPARARPR($lang = "es-ES_tradnl")
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':endParaRPr lang="'. $lang . '" />__GENERATEAP__';
        $this->_xmlChart = str_replace(
            '__GENERATEAP__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:numRef
     *
     * @access protected
     */
    protected function generateNUMREF()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':numRef>__GENERATESTRREF__</' . CreateGraphic::NAMESPACEWORD .
            ':numRef>__GENERATETX__';
        $this->_xmlChart = str_replace(
            '__GENERATETX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:formatCode
     *
     * @access protected
     * @param string $val
     */
    protected function generateFORMATCODE($val = 'General')
    {
        $this->_xmlChart = str_replace(
            '__GENERATESTRCACHE__',
            '<' . CreateGraphic::NAMESPACEWORD . ':formatCode>' . $val .
            '</' . CreateGraphic::NAMESPACEWORD .
            ':formatCode>__GENERATESTRCACHE__',
            $this->_xmlChart
        );
    }

    /**
     * Generate w:legend
     *
     * @access protected
     */
    protected function generateLEGEND()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':legend>__GENERATELEGEND__</' .
            CreateGraphic::NAMESPACEWORD . ':legend>__GENERATECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATECHART__',
            $xml,
            $this->_xmlChart
        );
    }

    /**
     * Generate c:legendPos
     *
     * @access protected
     * @param string $val
     */
    protected function generateLEGENDPOS($val = 'r')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':legendPos val="' .
             $val . '"></' . CreateGraphic::NAMESPACEWORD .
             ':legendPos>__GENERATELEGEND__';
        $this->_xmlChart = str_replace(
            '__GENERATELEGEND__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:layout
     *
     * @access protected
     * @param string $font
     */
    protected function generateLEGENDFONT($font = '')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':layout />' .
            '<' . CreateGraphic::NAMESPACEWORD . ':txPr>' .
            '<a:bodyPr /><a:lstStyle /><a:p><a:pPr><a:defRPr>' .
            '<a:latin typeface="' . $font . '" pitchFamily="34" charset="0" />' .
            '<a:cs typeface="' . $font . '" pitchFamily="34" charset="0" />' .
            '</a:defRPr></a:pPr><a:endParaRPr lang="es-ES" /></a:p>' .
            '</' . CreateGraphic::NAMESPACEWORD . ':txPr>';
        $this->_xmlChart = str_replace(
            '__GENERATELEGEND__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:overlay
     *
     * @access protected
     * @param string $val
     */
    protected function generateLEGENDOVERLAY($val = 0)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':overlay val="' .
             $val . '" />__GENERATELEGEND__';
        $this->_xmlChart = str_replace(
            '__GENERATELEGEND__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:poltVisOnly
     *
     * @access protected
     * @param string $val
     */
    protected function generatePLOTVISONLY($val = '1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':plotVisOnly val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':plotVisOnly>__GENERATECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:externalData
     *
     * @access protected
     * @param string $val
     */
    protected function generateEXTERNALDATA($val = 'rId1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':externalData r:id="' . $val . '"></' .
            CreateGraphic::NAMESPACEWORD . ':externalData>';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:spPr
     *
     * @access protected
     */
    protected function generateSPPR()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':spPr>__GENERATESPPR__</' . CreateGraphic::NAMESPACEWORD .
            ':spPr>__GENERATECHARTSPACE__';
        $this->_xmlChart = str_replace(
            '__GENERATECHARTSPACE__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:ln
     *
     * @access protected
     */
    protected function generateLN($w = NULL)
    {
        if(is_numeric($w)){
            $xml = '<' . CreateImage::NAMESPACEWORD1 . ':ln w="' . ($w * 12700) . '">__GENERATELN__</' .
                CreateImage::NAMESPACEWORD1 . ':ln>';
        }else{
            $xml = '<' . CreateImage::NAMESPACEWORD1 . ':ln>__GENERATELN__</' .
                CreateImage::NAMESPACEWORD1 . ':ln>';
        }
        $this->_xmlChart = str_replace(
            '__GENERATESPPR__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:noFill
     *
     * @access protected
     */
    protected function generateNOFILL()
    {
        $xml = '<' . CreateImage::NAMESPACEWORD1 . ':noFill></' .
            CreateImage::NAMESPACEWORD1 . ':noFill>';
        $this->_xmlChart = str_replace(
            '__GENERATELN__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:overlap
     *
     * @access protected
     * @param string $val
     */
    protected function generateOVERLAP($val = '100')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':overlap val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':overlap>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:shape
     *
     * @access protected
     * @param string $val
     */
    protected function generateSHAPE($val = 'box')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':shape val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':shape>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:bandFmts
     *
     * @access protected
     * @param string $val
     */
    protected function generateBANDFMTS($val = 'box')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':bandFmts />__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:axid
     *
     * @access protected
     * @param string $val
     */
    protected function generateAXID($val = '59034624')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':axId val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':axId>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:firstSliceAng
     *
     * @access protected
     * @param string $val
     */
    protected function generateFIRSTSLICEANG($val = '0')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':firstSliceAng val="' . $val . '"></' .
            CreateGraphic::NAMESPACEWORD . ':firstSliceAng>' . '__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:dLbls
     *
     * @access protected
     */
    protected function generateDLBLS()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':dLbls>__GENERATEDLBLS__</' . CreateGraphic::NAMESPACEWORD .
            ':dLbls>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }


    /**
     * Generate w:holeSize
     *
     * @access protected
     */
    protected function generateHOLESIZE($val = 50)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':holeSize val="' . $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':holeSize>__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:showPercent
     *
     * @access protected
     * @param string $val
     */
    protected function generateSHOWPERCENT($val = '0')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':showPercent val="' . $val . '"></' .
            CreateGraphic::NAMESPACEWORD . ':showPercent>';
        $this->_xmlChart = str_replace(
            '__GENERATEDLBLS__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:chart
     *
     * @access protected
     */
    protected function generateDOCUMENTCHART()
    {
        $this->_xml = str_replace(
            '__GENERATEGRAPHICDATA__',
            '<' . CreateGraphic::NAMESPACEWORD .
            ':chart xmlns:c="http://schemas.openxmlformats.org/drawingml/' .
            '2006/chart" xmlns:r="http://schemas.openxmlformats.org/offic' .
            'eDocument/2006/relationships" r:id="rId' . $this->getRId() .
            '"></' . CreateGraphic::NAMESPACEWORD .
            ':chart>',
            $this->_xml
        );
    }

    /**
     * Generate w:catAx
     *
     * @access protected
     */
    protected function generateCATAX()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':catAx>__GENERATEAX__</' . CreateGraphic::NAMESPACEWORD .
            ':catAx>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:dTable
     *
     * @access protected
     */
    protected function generateDATATABLE()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':dTable>' .
            '<' . CreateGraphic::NAMESPACEWORD . ':showHorzBorder val="1"/>' .
            '<' . CreateGraphic::NAMESPACEWORD . ':showVertBorder val="1"/>' .
            '<' . CreateGraphic::NAMESPACEWORD . ':showOutline val="1"/>' .
            '<' . CreateGraphic::NAMESPACEWORD . ':showKeys val="1"/>' .
            '</' . CreateGraphic::NAMESPACEWORD . ':dTable>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:valAx
     *
     * @access protected
     */
    protected function generateVALAX()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':valAx>__GENERATEAX__</' .
            CreateGraphic::NAMESPACEWORD .
            ':valAx>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:axId
     *
     * @access protected
     * @param <type> $val
     */
    protected function generateAXAXID($val = '59034624')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':axId val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':axId>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:scaling
     *
     * @access protected
     */
    protected function generateSCALING()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':scaling>__GENERATESCALING__</' . CreateGraphic::NAMESPACEWORD .
            ':scaling>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:orientation
     *
     * @access protected
     * @param string $val
     */
    protected function generateORIENTATION($val = 'minMax')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':orientation val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD . ':orientation>';
        $this->_xmlChart = str_replace(
            '__GENERATESCALING__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:axPos
     *
     * @access protected
     * @param string $val
     */
    protected function generateAXPOS($val = 'b')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':axPos val="' . $val .
            '"></' . CreateGraphic::NAMESPACEWORD . ':axPos>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:title
     *
     * @access protected
     * @param string $val
     */
    protected function generateAXLABEL($val = 'Axis title')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':title><c:tx><c:rich>' .
            '__GENERATEBODYPR__<a:lstStyle/><a:p><a:pPr><a:defRPr/></a:pPr>' .
            '<a:r><a:t>' . $val . '</a:t></a:r></a:p></c:rich></c:tx>' .
            '</' . CreateGraphic::NAMESPACEWORD . ':title>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate a:bodyPr
     *
     * @access protected
     * @param string $val
     */
    protected function generateAXLABELDISP($val = 'horz', $rot = 0)
    {
        $xml = '<a:bodyPr rot="' . $rot . '" vert="' . $val . '"/>';
        $this->_xmlChart = str_replace(
            '__GENERATEBODYPR__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:serAx
     *
     * @access protected
     */
    protected function generateSERAX()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':serAx>__GENERATEAX__</' .
            CreateGraphic::NAMESPACEWORD .
            ':serAx>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }



    /**
     * Generate c:scatterStyle
     *
     * @access protected
     */
    protected function generateSCATTERSTYLE($style = 'smoothMarker')
    {
        $possibleStyles = array('none', 'line', 'lineMarker', 'marker', 'smooth', 'smoothMarker');
        if(!in_array($style, $possibleStyles))
            $style = 'smoothMarker';
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':scatterStyle val="' . $style . '" />__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:tickLblPos
     *
     * @access protected
     * @param string $val
     */
    protected function generateTICKLBLPOS($val = 'nextTo')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':tickLblPos val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':tickLblPos>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:crossAx
     *
     * @access protected
     * @param string $val
     */
    protected function generateCROSSAX($val = '59040512')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':crossAx  val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':crossAx >__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:crosses
     *
     * @access protected
     * @param string $val
     */
    protected function generateCROSSES($val = 'autoZero')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':crosses val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':crosses>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:auto
     *
     * @access protected
     * @param string $val
     */
    protected function generateAUTO($val = '1')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':auto val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':auto>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:lblAlgn
     *
     * @access protected
     * @param string $val
     */
    protected function generateLBLALGN($val = 'ctr')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':lblAlgn val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':lblAlgn>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:lblOffset
     *
     * @access protected
     * @param string $val
     */
    protected function generateLBLOFFSET($val = '100')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':lblOffset val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD . ':lblOffset>';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:majorTickMark
     *
     * @access protected
     */
    protected function generateMAJORTICKMARK($val = 'none')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':majorTickMark val="'.$val.'"></' .
            CreateGraphic::NAMESPACEWORD . ':majorTickMark>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:majorGridlines
     *
     * @access protected
     */
    protected function generateMAJORGRIDLINES()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':majorGridlines></' .
            CreateGraphic::NAMESPACEWORD . ':majorGridlines>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:majorGridlines
     *
     * @access protected
     */
    protected function generateMARKER($symbol = 'none', $size = NULL)
    {
        $symbols = array('circle', 'dash', 'diamond', 'dot', 'none', 'picture', 'plus', 'square', 'star', 'triangle', 'x');
        if(!in_array($symbol, $symbols)){
            $symbol = 'none';
        }
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':marker>' .
            '<' . CreateGraphic::NAMESPACEWORD . ':symbol val="' . $symbol . '"/>';
        if(!empty($size) && is_int($size) && $size < 73 && $size > 1){
            $xml .= '<' . CreateGraphic::NAMESPACEWORD .':size val="'.$size.'"></' . CreateGraphic::NAMESPACEWORD .':size>';
        }
        $xml .= '</' . CreateGraphic::NAMESPACEWORD .':marker>__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:majorGridlines
     *
     * @access protected
     */
    protected function generateMINORGRIDLINES($val = '')
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':minorGridlines></' .
            CreateGraphic::NAMESPACEWORD . ':minorGridlines>__GENERATEAX__';
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:numFmt
     *
     * @access protected
     * @param string $formatCode
     * @param string $sourceLinked
     */
    protected function generateNUMFMT($formatCode='General',
                                      $sourceLinked = '1')
    {
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', '<' .
            CreateGraphic::NAMESPACEWORD .
            ':numFmt formatCode="' . $formatCode .
            '" sourceLinked="' . $sourceLinked . '"></' .
            CreateGraphic::NAMESPACEWORD . ':numFmt>__GENERATEAX__',
            $this->_xmlChart
        );
    }

    /**
     * Generate w:latin
     *
     * @access protected
     * @param string $font
     */
    protected function generateRFONTS($font)
    {
        $this->_xmlChart = str_replace(
            '__GENERATEDEFRPR__', '<' .
            CreateImage::NAMESPACEWORD1 . ':latin typeface="' .
            $font . '" pitchFamily="34" charset="0"></' .
            CreateImage::NAMESPACEWORD1 . ':latin ><' .
            CreateImage::NAMESPACEWORD1 . ':cs typeface="' .
            $font . '" pitchFamily="34" charset="0"></' .
            CreateImage::NAMESPACEWORD1 . ':cs>', $this->_xmlChart
        );
    }


    /**
     * Generate w:crossBetween
     *
     * @access protected
     * @param string $val
     */
    protected function generateCROSSBETWEEN($val = 'between')
    {
        $this->_xmlChart = str_replace(
            '__GENERATEAX__', '<' .
            CreateGraphic::NAMESPACEWORD . ':crossBetween val="' .
            $val . '"></' . CreateGraphic::NAMESPACEWORD .
            ':crossBetween>',
            $this->_xmlChart
        );
    }



    /**
     * Generate w:ofPieChart
     *
     * @access protected
     * @param string $val
     */
    protected function generateOFPIECHART()
    {
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', '<' .
            CreateGraphic::NAMESPACEWORD . ':ofPieChart>'.
            '__GENERATETYPECHART__' .
            '</' . CreateGraphic::NAMESPACEWORD . ':ofPieChart>',
            $this->_xmlChart
        );
    }

    /**
     * Generate c:ofPieType
     *
     * @access protected
     * @param string $val
     */
    protected function generateOFPIETYPE($val = 'pie')
    {
        if(!in_array($val, array('pie', 'bar')))
            $val = 'pie';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', '<' .
            CreateGraphic::NAMESPACEWORD . ':ofPieType val="' . $val . '">'.
            '</' . CreateGraphic::NAMESPACEWORD . ':ofPieType>' .
            '__GENERATETYPECHART__', $this->_xmlChart
        );
    }
    /**
     * Generate w:scatterChart
     *
     * @access protected
     */
    protected function generateSCATTERCHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':scatterChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':scatterChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate w:doughnutChart
     *
     * @access protected
     */
    protected function generateDOUGHNUTCHART()
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD .
            ':doughnutChart>__GENERATETYPECHART__</' .
            CreateGraphic::NAMESPACEWORD .
            ':doughnutChart>__GENERATEPLOTAREA__';
        $this->_xmlChart = str_replace(
            '__GENERATEPLOTAREA__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:GAPWIDTH
     *
     * @access protected
     * @param string $val
     */
    protected function generateGAPWIDTH($val = 100)
    {
        if(!is_numeric($val))
            $val = 100;
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', '<' .
            CreateGraphic::NAMESPACEWORD . ':gapWidth val="' . $val . '">'.
            '</' . CreateGraphic::NAMESPACEWORD . ':gapWidth>' .
            '__GENERATETYPECHART__', $this->_xmlChart
        );
    }

    /**
     * Generate c:secondPieSize
     *
     * @access protected
     * @param string $val
     */
    protected function generateSECONDPIESIZE($val = 75)
    {
        if(!is_numeric($val))
            $val = 75;
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', '<' .
            CreateGraphic::NAMESPACEWORD . ':secondPieSize val="' . $val . '">'.
            '</' . CreateGraphic::NAMESPACEWORD . ':secondPieSize>' .
            '__GENERATETYPECHART__', $this->_xmlChart
        );
    }

    /**
     * Generate c:serLines
     *
     * @access protected
     */
    protected function generateSERLINES()
    {
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', '<' .
            CreateGraphic::NAMESPACEWORD . ':serLines>'.
            '</' . CreateGraphic::NAMESPACEWORD . ':serLines>' .
            '__GENERATETYPECHART__', $this->_xmlChart
        );
    }

    /**
     * Generate c:splitType
     *
     * @access protected
     * @param string $val
     */
    protected function generateSPLITTYPE($val)
    {
        if(!in_array($val, array('auto', 'cust', 'percent', 'pos', 'val')))
            $xml = '<' . CreateGraphic::NAMESPACEWORD . ':splitType>'.
                '</' . CreateGraphic::NAMESPACEWORD . ':splitType>' .
                '__GENERATETYPECHART__';
        else
            $xml = '<' . CreateGraphic::NAMESPACEWORD . ':splitType val="' . $val . '">'.
                '</' . CreateGraphic::NAMESPACEWORD . ':splitType>' .
                '__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }


    /**
     * Generate c:custSplit
     *
     * @access protected
     */
    protected function generateCUSTSPLIT()
    {
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', '<' .
            CreateGraphic::NAMESPACEWORD . ':custSplit>'.
            '__GENERATECUSTSPLIT__' .
            '</' . CreateGraphic::NAMESPACEWORD . ':custSplit>' .
            '__GENERATETYPECHART__', $this->_xmlChart
        );
    }

    /**
     * Generate c:splitType
     *
     * @access protected
     * @param string $val
     */
    protected function generateSECONDPIEPT($val)
    {
        $xml = "";
        if(is_array($val)){
            foreach ($val as $value) {
                $xml .= '<' . CreateGraphic::NAMESPACEWORD . ':secondPiePt val="' . $value . '">'.
                    '</' . CreateGraphic::NAMESPACEWORD . ':secondPiePt>';
            }
        }
        $this->_xmlChart = str_replace(
            '__GENERATECUSTSPLIT__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:splitPos
     *
     * @access protected
     * @param string $val
     */
    protected function generateSPLITPOS($val, $type = "auto")
    {
        if($type == 'pos')
            $val = (int)$val;
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':splitPos val="' . $val . '">'.
            '</' . CreateGraphic::NAMESPACEWORD . ':splitPos>' .
            '__GENERATETYPECHART__';
        $this->_xmlChart = str_replace(
            '__GENERATETYPECHART__', $xml, $this->_xmlChart
        );
    }

    /**
     * Generate c:explosion
     *
     * @access protected
     * @param string $val
     */
    protected function generateEXPLOSION($val = 25)
    {
        $xml = '<' . CreateGraphic::NAMESPACEWORD . ':explosion val="' . $val . '">'.
            '</' . CreateGraphic::NAMESPACEWORD . ':explosion>' .
            '__GENERATESER__';
        $this->_xmlChart = str_replace(
            '__GENERATESER__', $xml, $this->_xmlChart
        );
    }

    /**
     * Create chart xml
     *
     * @access protected
     * @param array $args[0]
     */
    protected function createCHARTXML()
    {
        $this->_xmlChart = '';
        $args = func_get_args();
        $this->setRId($args[0][0]);
        $this->initGraphic($args[0][1]);
        $this->createEmbeddedXmlChart();
        return true;
    }

    /**
     * Clean tags in template document
     *
     * @access protected
     */
    protected function cleanTemplateDocument()
    {
        $this->_xmlChart = preg_replace('/__[A-Z]+__/', '', $this->_xmlChart);
    }



    /**
     * Clean tags in template document
     *
     * @access protected
     */
    public static function cleanTemplateChart($xml = "")
    {
        return preg_replace('/__[A-Z]+__/', '', $xml);
    }

    /**
     * Clean tags in template document
     *
     * @access protected
     */
    protected function cleanTemplate2()
    {
        $this->_xmlChart = preg_replace(
            array(
                '/__GENERATE[A-B,D-O,Q-R,U-Z][A-Z]+__/',
                '/__GENERATES[A-D,F-Z][A-Z]+__/', '/__GENERATETX__/'),
            '',
            $this->_xmlChart
        );
    }

    /**
     * Clean tags in template document
     *
     * @access protected
     */
    protected function cleanTemplateFonts()
    {
        $this->_xmlChart = preg_replace(
            '/__GENERATETITLE[A-Z]+__/',
            '',
            $this->_xmlChart
        );
    }

    /**
     * Clean tags in template document
     *
     * @access protected
     */
    protected function cleanTemplate3()
    {
        $this->_xmlChart = preg_replace(
            array(
                '/__GENERATE[A-B,D-O,Q-S,U-Z][A-Z]+__/',
                '/__GENERATES[A-D,F-Z][A-Z]+__/',
                '/__GENERATETX__/'
                ),
            '',
            $this->_xmlChart
        );
    }

    /**
     * Generate c:txPr
     *
     * @access protected
     * @param string $font
     */
    protected function generateRFONTS2($font)
    {
        $this->_xmlChart = str_replace(
            '__GENERATEAX__',
            '<c:txPr><a:bodyPr /><a:lstStyle /><a:p>' .
            '<a:pPr><a:defRPr><a:latin typeface="' .
            $font . '" pitchFamily="34" charset="0" /><a:cs typeface="' .
            $font . '" pitchFamily="34" charset="0" /></a:defRPr>' .
            '</a:pPr><a:endParaRPr lang="es-ES" /></a:p></c:txPr>' .
            '__GENERATEAX__', $this->_xmlChart
        );
    }

    /**
     * Generate table
     *
     * @param int $rows
     * @param int $cols
     * @access protected
     */
    protected function generateTABLE($rows, $cols)
    {
        $word = 'A';
        for ($i = 0; $i < $cols; $i++)
            $word++;
        $rows++;
        $this->_xml = '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>'.
                      '<table xmlns="http://schemas.openxmlformats.org/spreads'.
                      'heetml/2006/main" id="1" name="Tabla1" displayName='.
                      '"Tabla1" ref="A1:' . $word . $rows .
                      '" totalsRowShown="0" tableBorderDxfId="0">'.
                      '__GENERATETABLE__</table>';
    }

    /**
     * Generate tablecolumn
     *
     * @param string $id
     * @param string $name
     * @access protected
     */
    protected function generateTABLECOLUMN($id = '2', $name = '')
    {
        $xml =  '<tableColumn id="' . $id . '" name="' . $name .
                '"></tableColumn >__GENERATETABLECOLUMNS__';

        $this->_xml = str_replace(
            '__GENERATETABLECOLUMNS__', $xml, $this->_xml
        );
    }

    /**
     * Generate tablecolumns
     *
     * @param string $count
     * @access protected
     */
    protected function generateTABLECOLUMNS($count = '2')
    {
        $xml = '<tableColumns count="' . $count .
               '">__GENERATETABLECOLUMNS__</tableColumns>__GENERATETABLE__';

        $this->_xml = str_replace('__GENERATETABLE__', $xml, $this->_xml);
    }

    /**
     * Generate tablestyleinfo
     *
     * @param string $showFirstColumn
     * @param string $showLastColumn
     * @param string $showRowStripes
     * @param string $showColumnStripes
     * @access protected
     */
    protected function generateTABLESTYLEINFO($showFirstColumn = '0',
                                               $showLastColumn  = "0",
                                               $showRowStripes  = "1",
                                               $showColumnStripes = "0")
    {
        $xml = '<tableStyleInfo   showFirstColumn="' . $showFirstColumn .
               '" showLastColumn="' . $showLastColumn .
               '" showRowStripes="' . $showRowStripes .
               '" showColumnStripes="' . $showColumnStripes .
               '"></tableStyleInfo >';

        $this->_xml = str_replace('__GENERATETABLE__', $xml, $this->_xml);
    }
}