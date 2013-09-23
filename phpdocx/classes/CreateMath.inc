<?php

/**
 * Add a math eq
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

class CreateMath extends CreateElement
{

    /**
     *
     * @access private
     * @static
     */
    private static $_instance = null;
    /**
     *
     * @access private
     * @var string
     */
    private $_mathML;

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
     * Magic method, returns current MathML
     *
     * @access public
     * @return string Return current MathML
     */
    public function __toString()
    {
        return $this->_mathML;
    }

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @return CreateLink
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreateMath();
        }
        return self::$_instance;
    }

    /**
     * Getter. Access to mathXML var
     *
     * @access public
     * @return string
     */
    public function getMathXML()
    {
        return $this->_mathML;
    }


    /**
     * Getter. Access to mathXML var
     *
     * @access public
     * @param string $mathML
     */
    public function setMathXML($mathML)
    {
        $this->_mathML = $mathML;
    }

    /**
     * Generate a new MathML eq
     *
     * @access public
     * @param string $arrArgs[0] Math eq
     */
    public function createMath()
    {
        $this->_xml = '';
        $arrArgs = func_get_args();

        $this->transformMath($arrArgs[0]);
    }

    /**
     * Transform a MathML eq using XSL
     *
     * @access protected
     * @param string $mathML Math eq
     */
    protected function transformMath($mathML)
    {
        $arrDeleteStrsMML = array('<mi>', '</mi>');
        $arrDeleteToStrsMML = array('<mn>', '</mn>');
        $mathML = str_replace($arrDeleteStrsMML, $arrDeleteToStrsMML, $mathML);

        $rscXML = new DOMDocument();
        $rscXML->loadXML($mathML);
        $objXSLTProc = new XSLTProcessor();
        $objXSL = new DOMDocument();
        $objXSL->load('../xsl/MML2OMML_n.XSL');
        $objXSLTProc->importStylesheet($objXSL);

        $this->_mathML = $objXSLTProc->transformToXML($rscXML);
        $arrOMML = array('<?xml version="1.0" encoding="UTF-8"?>',
            ' xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/'
            . 'math" xmlns:mml="http://www.w3.org/1998/Math/MathML"');
        $arrToOMML = array('', '');
        $this->_mathML = str_replace($arrOMML, $arrToOMML, $this->_mathML);
    }

}
