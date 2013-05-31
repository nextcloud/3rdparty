<?php

/**
 * Create Pie Chart
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

class CreatePieChart extends CreateGraphic implements InterfaceGraphic
{
    /**
     * Create embedded xml chart
     *
     * @access public
     */
    public function createEmbeddedXmlChart(){

        $this->_xmlChart = '';
        $this->generateCHARTSPACE();
        $this->generateDATE1904(1);
        $this->generateLANG();
        $color = 2;
        if ($this->_color) {
            $color = $this->_color;
        }
        $this->generateSTYLE($color);
        $this->generateCHART();
        if ($this->_title != '') {
            $this->generateTITLE();
        } else {
            $this->generateAUTOTITLEDELETED();
            $title = '';
        }
        if ($this->values == '') {
            exit('You haven`t added data');
        }
        $this->generatePLOTAREA();
        $this->generateLAYOUT();
        $this->generatePIECHART();

        $this->generateVARYCOLORS();

        if (isset($this->values['legend'])) {
            $legends = array($this->_title);
            $numValues = count($this->values) -1;
        }else {
            $legends = array($this->_title);
            $numValues = count($this->values);
        }
        $letter = 'A';
        for ($i = 0; $i < count($legends); $i++) {
            $this->generateSER();
            $this->generateIDX($i);
            $this->generateORDER($i);
            $letter++;

            $this->generateTX();
            $this->generateSTRREF();
            $this->generateF('Sheet1!$' . $letter . '$1');
            $this->generateSTRCACHE();
            $this->generatePTCOUNT();
            $this->generatePT();
            $this->generateV($this->_title);
            if(!empty($this->_explosion) && is_numeric($this->_explosion)){
                    $this->generateEXPLOSION($this->_explosion);
            }
            $this->cleanTemplate2();

            if(!empty($this->_showValue) || !empty($this->_showCategory)){
                $this->generateSERDLBLS();
                if(!empty($this->_showValue))
                    $this->generateSHOWVAL();
                if(!empty($this->_showCategory))
                    $this->generateSHOWCATNAME();
                if(!empty($this->_showPercent))
                    $this->generateSHOWPERCENT(1);
            }

            $this->generateCAT();
            $this->generateSTRREF();
            $this->generateF('Sheet1!$A$2:$A$' . ($numValues + 1));
            $this->generateSTRCACHE();
            $this->generatePTCOUNT($numValues);
            $num = 0;
            foreach ($this->values as $legend => $value) {
                if ($legend == 'legend') {
                    continue;
                }
                $this->generatePT($num);
                $this->generateV($legend);
                $num++;
            }
            $this->cleanTemplate2();
            $this->generateVAL();
            $this->generateNUMREF();
            $this->generateF('Sheet1!$' . $letter . '$2:$B$' . ($numValues + 1));
            $this->generateNUMCACHE();
            $this->generateFORMATCODE();
            $this->generatePTCOUNT($numValues);
            $num = 0;
            foreach ($this->values as $legend => $value) {
                if ($legend == 'legend') {
                    continue;
                }
                $this->generatePT($num);
                $this->generateV($value[$i]);
                $num++;
            }
            $this->cleanTemplate3();
        }

        $this->generateDLBLS();
        $showPercent = 0;
        if ($this->_showPercent != '') {
            $showPercent = 1;
        }
        $this->generateSHOWPERCENT($showPercent);
        if(strpos($this->_type, '3D') === false)
            $this->generateFIRSTSLICEANG();

        if ($this->_legendPos != 'none') {
            $this->generateLEGEND();
            if (!empty($this->_legendPos)) {
                $this->generateLEGENDPOS($this->_legendPos);
            }
            if (!empty($this->_legendOverlay)) {
                $this->generateLEGENDOVERLAY($this->_legendOverlay);
            }
        }
        $this->generatePLOTVISONLY();

        if ((!isset($this->_border) || $this->_border == 0 || !is_numeric($this->_border))
        ) {
            $this->generateSPPR();
            $this->generateLN();
            $this->generateNOFILL();
        }else{
            $this->generateSPPR();
            $this->generateLN($this->_border);
        }

        if ($this->_font != '') {
            $this->generateTXPR();
            $this->generateLEGENDBODYPR();
            $this->generateLSTSTYLE();
            $this->generateAP();
            $this->generateAPPR();
            $this->generateDEFRPR();
            $this->generateRFONTS($this->_font);
            $this->generateENDPARARPR();
        }



        $this->generateEXTERNALDATA();
        $this->cleanTemplateDocument();
        return $this->_xmlChart;

    }

    public function dataTag(){
        return array('val');
    }

    /**
     * Create excel table
     *
     * @access public
     * @param string args[0]
     * @param string args[1]
     */
    public function addTable()
    {
        $this->_xml = '';
        $args = func_get_args();
        $dats = $args[0];
        $szDats = count($dats);
        foreach ($dats as $ind => $data) {
            $szCols = count($data);
            break;
        }
        $szDats = count($dats);
        $szCols = 1;
        $this->generateTABLE($szDats, $szCols);
        $this->generateTABLECOLUMNS($szCols + 1);
        $this->generateTABLECOLUMN(1, ' ');
        $this->generateTABLECOLUMN(2, '0');
        $this->generateTABLESTYLEINFO();
        $this->cleanTemplate();
    }


    /**
     * retrun the type of the xlsx object
     *
     * @access public
     */
    public function getXlsxType(){
        return CreateSimpleXlsx::getInstance();
    }

}