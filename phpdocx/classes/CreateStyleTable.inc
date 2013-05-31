<?php

/**
 * Create style table
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

class CreateStyleTable extends CreateStyle
{

    /**
     * @access protected
     * @var string
     */
    protected $_xml;
    /**
     * @access private
     * @var CreateStyleTable
     * @static
     */
    private static $_instance = NULL;

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
        return $this->_xml;
    }

    /**
     *
     * @access public
     * @return CreateStyleTable
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreateStyleTable();
        }
        return self::$_instance;
    }

    /**
     * Add table style
     *
     * @access public
     * @param array $args[0]
     */
    public function addStyleTable()
    {
        $this->_xml = '';
        $args = func_get_args();
        if (isset($args[0]['type'])) {
            $this->generateTBLSTYLEPR($args[0]['type']);
        }
        if (isset($args[0]['name'])) {
            $this->generateNAME($args[0]['name']);
        }
        if (isset($args[0]['basedOn'])) {
            $this->generateBASEDON($args[0]['basedOn']);
        }
        if (isset($args[0]['next'])) {
            $this->generateNEXT($args[0]['next']);
        }
        if (isset($args[0]['link'])) {
            $this->generateLINK($args[0]['link']);
        }
        if (isset($args[0]['autoRedefine'])) {
            $this->generateAUTOREDEFINE();
        }
        if (isset($args[0]['uiPriority'])) {
            $this->generateUIPRIORITY($args[0]['uiPriority']);
        }
        if (isset($args[0]['semiHidden'])) {
            $this->generateSEMIHIDDEN();
        }
        if (isset($args[0]['unhideWhenUsed'])) {
            $this->generateUNHIDEWHENUSED();
        }
        if (isset($args[0]['qFormat'])) {
            $this->generateQFORMAT();
        }
        if (isset($args[0]['rsid'])) {
            $this->generateRSID($args[0]['rsid']);
        }
        if (isset($args[0]['keepNext']) ||
            isset($args[0]['keepLines']) ||
            (isset($args[0]['spacing_before']) ||
            isset($args[0]['spacing_after']) ||
            isset($args[0]['spacing_line']) ||
            isset($args[0]['spacing_lineRule'])) ||
            isset($args[0]['outlineLvl']) ||
            isset($args[0]['contextualSpacing']) ||
            isset($args[0]['ilvl']) ||
            isset($args[0]['ind_left'])
        ) {
            $this->generatePPR();
            if (isset($args[0]['keepNext'])) {
                $this->generateKEEPNEXT();
            }
            if (isset($args[0]['keepLines'])) {
                $this->generateKEEPLINES($args[0]['keepLines']);
            }
            if (isset($args[0]['pBdr_bottom_val']) &&
                isset($args[0]['pBdr_bottom_sz']) &&
                isset($args[0]['pBdr_bottom_space']) &&
                isset($args[0]['pBdr_bottom_color']) &&
                isset($args[0]['pBdr_bottom_themeColor'])
            ) {
                $this->generatePBDR();
                $this->generatePBDR_BOTTOM(
                    $args[0]['pBdr_bottom_val'],
                    $args[0]['pBdr_bottom_sz'],
                    $args[0]['pBdr_bottom_space'],
                    $args[0]['pBdr_bottom_color'],
                    $args[0]['pBdr_bottom_themeColor']
                );
            }
            if (isset($args[0]['tab_center']) || isset($args[0]['tab_right'])) {
                $this->generateTABS();
                if (isset($args[0]['tab_center'])) {
                    $this->generateTABCENTER($args[0]['tab_center']);
                }
                if (isset($args[0]['tab_right'])) {
                    $this->generateTABRIGHT($args[0]['tab_right']);
                }
            }
            if (isset($args[0]['spacing_before']) ||
                isset($args[0]['spacing_after']) ||
                isset($args[0]['spacing_line']) ||
                isset($args[0]['spacing_lineRule'])
            ) {
                if (!isset($args[0]['spacing_before'])) {
                    $args[0]['spacing_before'] = '';
                }
                if (!isset($args[0]['spacing_after'])) {
                    $args[0]['spacing_after'] = '';
                }
                if (!isset($args[0]['spacing_line'])) {
                    $args[0]['spacing_line'] = '';
                }
                if (!isset($args[0]['spacing_lineRule'])) {
                    $args[0]['spacing_lineRule'] = '';
                }
                
                $this->generateSPACING(
                    $args[0]['spacing_before'],
                    $args[0]['spacing_after'],
                    $args[0]['spacing_line'],
                    $args[0]['spacing_lineRule']
                );
            }
            if (isset($args[0]['ind_left'])) {
                $this->generateIND($args[0]['ind_left']);
            }
            if (isset($args[0]['contextualSpacing'])) {
                $this->generateCONTEXTUALSPACING();
            }
            if (isset($args[0]['outlineLvl'])) {
                $this->generateOUTLINELVL($args[0]['outlineLvl']);
            }
            if (isset($args[0]['ilvl'])) {
                $this->generateNUMPR();
                $this->generateILVL($args[0]['ilvl']);
            }
        }
        if ((isset($args[0]['rFonts_asciiTheme']) &&
            isset($args[0]['rFonts_eastAsiaTheme']) &&
            isset($args[0]['rFonts_hAnsiTheme']) &&
            isset($args[0]['rFonts_cstheme'])) ||
            isset($args[0]['b']) ||
            isset($args[0]['bCs']) ||
            isset($args[0]['i']) ||
            isset($args[0]['iCs']) ||
            isset($args[0]['u']) ||
            isset($args[0]['color_val']) ||
            isset($args[0]['sz']) ||
            isset($args[0]['szCs']) ||
            isset($args[0]['kern']) ||
            isset($args[0]['rPr_spacing']) ||
            isset($args[0]['u'])
        ) {

            $this->generateRPR();
            if (isset($args[0]['rFonts_asciiTheme']) &&
                isset($args[0]['rFonts_eastAsiaTheme']) &&
                isset($args[0]['rFonts_hAnsiTheme']) &&
                isset($args[0]['rFonts_cstheme'])
            ) {
                $this->generateRFONTS(
                    $args[0]['rFonts_asciiTheme'],
                    $args[0]['rFonts_eastAsiaTheme'],
                    $args[0]['rFonts_hAnsiTheme'],
                    $args[0]['rFonts_cstheme']
                );
            }
            if (isset($args[0]['rFonts_ascii']) &&
                isset($args[0]['rFonts_hAnsi']) &&
                isset($args[0]['rFonts_cs'])
            ) {
                $this->generateRFONTS2(
                    $args[0]['rFonts_ascii'],
                    $args[0]['rFonts_hAnsi'],
                    $args[0]['rFonts_cs']
                );
            }
            if (isset($args[0]['b'])) {
                $this->generateB();
            }
            if (isset($args[0]['bCs'])) {
                $this->generateBCS();
            }
            if (isset($args[0]['i'])) {
                $this->generateI($args[0]['i']);
            }
            if (isset($args[0]['iCs'])) {
                $this->generateICS($args[0]['iCs']);
            }
            if (isset($args[0]['u'])) {
                $this->generateU();
            }
            if (isset($args[0]['color_val'])) {
                if (!isset($args[0]['color_themeColor'])) {
                    $args[0]['color_themeColor'] = '';
                }
                if (!isset($args[0]['color_themeShade'])) {
                    $args[0]['color_themeShade'] = '';
                }
                
                $this->generateCOLOR(
                    $args[0]['color_val'],
                    $args[0]['color_themeColor'],
                    $args[0]['color_themeShade']
                );
            }
            if (isset($args[0]['u'])) {
                $this->generateU($args[0]['u']);
            }
            if (isset($args[0]['rPr_spacing'])) {
                $this->generateRPR_SPACING($args[0]['rPr_spacing']);
            }
            if (isset($args[0]['kern'])) {
                $this->generateKERN($args[0]['kern']);
            }
            if (isset($args[0]['sz'])) {
                $this->generateSZ($args[0]['sz']);
            }
            if (isset($args[0]['szCs'])) {
                $this->generateSZCS($args[0]['szCs']);
            }
        }
        if (isset($args[0]['tblPr'])) {
            $this->generateTBLPR();
        }
        if ((isset($args[0]['top_w']) &&
            isset($args[0]['top_type'])) ||
            (isset($args[0]['left_w']) &&
            isset($args[0]['left_type'])) ||
            (isset($args[0]['bottom_w']) &&
            isset($args[0]['bottom_type'])) ||
            (isset($args[0]['right_w']) &&
            isset($args[0]['right_type'])) ||
            (isset($args[0]['tblInd_w']) &&
            isset($args[0]['tblInd_type'])) &&
            isset($args[0]['tblborder_top_val']) ||
            isset($args[0]['tblborder_left_val']) ||
            isset($args[0]['tblborder_bottom_val']) ||
            isset($args[0]['tblborder_right_val']) ||
            isset($args[0]['tblborder_insideH_val']) ||
            isset($args[0]['tblborder_insideV_val']) ||
            (isset($args[0]['shd_val']) &&
            isset($args[0]['shd_color']) &&
            isset($args[0]['shd_fill']) &&
            isset($args[0]['shd_themeFill']))
        ) {
            $this->generateTCPR();
            if (isset($args[0]['tbl_style_row'])) {
                $this->generateTBLSTYLEROWBANDSIZE($args[0]['tbl_style_row']);
            }
            if (isset($args[0]['tbl_style_col'])) {
                $this->generateTBLSTYLECOLBANDSIZE($args[0]['tbl_style_col']);
            }

            if (isset($args[0]['tblInd_w']) &&
                isset($args[0]['tblInd_type'])
            ) {

                $this->generateTBLIND(
                    $args[0]['tblInd_w'],
                    $args[0]['tblInd_type']
                );
            }

            if (isset($args[0]['tblborder_top_val']) ||
                isset($args[0]['tblborder_left_val']) ||
                isset($args[0]['tblborder_bottom_val']) ||
                isset($args[0]['tblborder_right_val']) ||
                isset($args[0]['tblborder_insideH_val']) ||
                isset($args[0]['tblborder_insideV_val'])
            ) {
                $this->generateTCBORDERS();
                if (isset($args[0]['tblborder_top_val'])) {
                    if (!isset($args[0]['tblborder_top_sz'])) {
                        $args[0]['tblborder_top_sz'] = '';
                    }
                    if (!isset($args[0]['tblborder_top_space'])) {
                        $args[0]['tblborder_top_space'] = '';
                    }
                    if (!isset($args[0]['tblborder_top_color'])) {
                        $args[0]['tblborder_top_color'] = '';
                    }
                    if (!isset($args[0]['tblborder_top_themeColor'])) {
                        $args[0]['tblborder_top_themeColor'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeTint'])) {
                        $args[0]['tblborder_insideV_themeTint'] = '';
                    }
                    
                    $this->generateTBLBORDERS_TOP(
                        $args[0]['tblborder_top_val'],
                        $args[0]['tblborder_top_sz'],
                        $args[0]['tblborder_top_space'],
                        $args[0]['tblborder_top_color'],
                        $args[0]['tblborder_top_themeColor'],
                        $args[0]['tblborder_insideV_themeTint']
                    );
                }
                if (isset($args[0]['tblborder_left_val'])) {
                    if (!isset($args[0]['tblborder_left_sz'])) {
                        $args[0]['tblborder_left_sz'] = '';
                    }
                    if (!isset($args[0]['tblborder_left_space'])) {
                        $args[0]['tblborder_left_space'] = '';
                    }
                    if (!isset($args[0]['tblborder_left_color'])) {
                        $args[0]['tblborder_left_color'] = '';
                    }
                    if (!isset($args[0]['tblborder_left_themeColor'])) {
                        $args[0]['tblborder_left_themeColor'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeTint'])) {
                        $args[0]['tblborder_insideV_themeTint'] = '';
                    }
                    
                    $this->generateTBLBORDERS_LEFT(
                        $args[0]['tblborder_left_val'],
                        $args[0]['tblborder_left_sz'],
                        $args[0]['tblborder_left_space'],
                        $args[0]['tblborder_left_color'],
                        $args[0]['tblborder_left_themeColor'],
                        $args[0]['tblborder_insideV_themeTint']
                    );
                }
                if (isset($args[0]['tblborder_bottom_val'])) {
                    if (!isset($args[0]['tblborder_bottom_sz'])) {
                        $args[0]['tblborder_bottom_sz'] = '';
                    }
                    if (!isset($args[0]['tblborder_bottom_space'])) {
                        $args[0]['tblborder_bottom_space'] = '';
                    }
                    if (!isset($args[0]['tblborder_bottom_color'])) {
                        $args[0]['tblborder_bottom_color'] = '';
                    }
                    if (!isset($args[0]['tblborder_bottom_themeColor'])) {
                        $args[0]['tblborder_bottom_themeColor'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeTint'])) {
                        $args[0]['tblborder_insideV_themeTint'] = '';
                    }
                    
                    $this->generateTBLBORDERS_BOTTOM(
                        $args[0]['tblborder_bottom_val'],
                        $args[0]['tblborder_bottom_sz'],
                        $args[0]['tblborder_bottom_space'],
                        $args[0]['tblborder_bottom_color'],
                        $args[0]['tblborder_bottom_themeColor'],
                        $args[0]['tblborder_insideV_themeTint']
                    );
                }
                if (isset($args[0]['tblborder_right_val'])) {
                    if (!isset($args[0]['tblborder_right_sz'])) {
                        $args[0]['tblborder_right_sz'] = '';
                    }
                    if (!isset($args[0]['tblborder_right_space'])) {
                        $args[0]['tblborder_right_space'] = '';
                    }
                    if (!isset($args[0]['tblborder_right_color'])) {
                        $args[0]['tblborder_right_color'] = '';
                    }
                    if (!isset($args[0]['tblborder_right_themeColor'])) {
                        $args[0]['tblborder_right_themeColor'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeTint'])) {
                        $args[0]['tblborder_insideV_themeTint'] = '';
                    }
                    
                    $this->generateTBLBORDERS_RIGHT(
                        $args[0]['tblborder_right_val'],
                        $args[0]['tblborder_right_sz'],
                        $args[0]['tblborder_right_space'],
                        $args[0]['tblborder_right_color'],
                        $args[0]['tblborder_right_themeColor'],
                        $args[0]['tblborder_insideV_themeTint']
                    );
                }
                if (isset($args[0]['tblborder_insideH_val'])) {
                    if (!isset($args[0]['tblborder_insideH_sz'])) {
                        $args[0]['tblborder_insideH_sz'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideH_space'])) {
                        $args[0]['tblborder_insideH_space'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideH_color'])) {
                        $args[0]['tblborder_insideH_color'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideH_themeColor'])) {
                        $args[0]['tblborder_insideH_themeColor'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeTint'])) {
                        $args[0]['tblborder_insideV_themeTint'] = '';
                    }
                    
                    $this->generateTBLBORDERS_INSIDEH(
                        $args[0]['tblborder_insideH_val'],
                        $args[0]['tblborder_insideH_sz'],
                        $args[0]['tblborder_insideH_space'],
                        $args[0]['tblborder_insideH_color'],
                        $args[0]['tblborder_insideH_themeColor'],
                        $args[0]['tblborder_insideV_themeTint']
                    );
                }
                if (isset($args[0]['tblborder_insideV_val'])) {
                    if (!isset($args[0]['tblborder_insideV_sz'])) {
                        $args[0]['tblborder_insideV_sz'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_space'])) {
                        $args[0]['tblborder_insideV_space'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_color'])) {
                        $args[0]['tblborder_insideV_color'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeColor'])) {
                        $args[0]['tblborder_insideV_themeColor'] = '';
                    }
                    if (!isset($args[0]['tblborder_insideV_themeTint'])) {
                        $args[0]['tblborder_insideV_themeTint'] = '';
                    }
                    
                    $this->generateTBLBORDERS_INSIDEV(
                        $args[0]['tblborder_insideV_val'],
                        $args[0]['tblborder_insideV_sz'],
                        $args[0]['tblborder_insideV_space'],
                        $args[0]['tblborder_insideV_color'],
                        $args[0]['tblborder_insideV_themeColor'],
                        $args[0]['tblborder_insideV_themeTint']
                    );
                }
            }
            if (isset($args[0]['shd_val']) &&
                isset($args[0]['shd_color']) &&
                isset($args[0]['shd_fill']) &&
                isset($args[0]['shd_themeFill'])
            ) {
                if (!isset($args[0]['shd_themeFillTint'])) {
                    $args[0]['shd_themeFillTint'] = '';
                }
                
                $this->generateSHD(
                    $args[0]['shd_val'],
                    $args[0]['shd_color'],
                    $args[0]['shd_fill'],
                    $args[0]['shd_themeFill'],
                    $args[0]['shd_themeFillTint']
                );
            }
            if ((isset($args[0]['top_w']) &&
                isset($args[0]['top_type'])) ||
                (isset($args[0]['left_w']) &&
                isset($args[0]['left_type'])) ||
                (isset($args[0]['bottom_w']) &&
                isset($args[0]['bottom_type'])) ||
                (isset($args[0]['right_w']) &&
                isset($args[0]['right_type']))
            ) {
                $this->generateTBLCELLMAR();

                if (isset($args[0]['top_w']) &&
                    isset($args[0]['top_type'])) {
                    $this->generateTOP(
                        $args[0]['top_w'],
                        $args[0]['top_type']
                    );
                }
                if (isset($args[0]['left_w']) &&
                    isset($args[0]['left_type'])) {
                    $this->generateLEFT(
                        $args[0]['left_w'],
                        $args[0]['left_type']
                    );
                }
                if (isset($args[0]['bottom_w']) &&
                    isset($args[0]['bottom_type'])) {
                    $this->generateBOTTOM(
                        $args[0]['bottom_w'],
                        $args[0]['bottom_type']
                    );
                }
                if (isset($args[0]['right_w']) &&
                    isset($args[0]['right_type'])) {
                    $this->generateRIGHT(
                        $args[0]['right_w'],
                        $args[0]['right_type']
                    );
                }
            }
        }
        $this->cleanTemplate();
        $this->_xml .= '__GENERATESTYLE__';
    }

    /**
     * Generate w:tblStylePr
     *
     * @access protected
     * @param string $type
     */
    protected function generateTBLSTYLEPR($type)
    {
        $this->_xml .= '<' . CreateElement::NAMESPACEWORD .
            ':tblStylePr ' . CreateElement::NAMESPACEWORD .
            ':type="' . $type . '">__GENERATESTYLE__</' .
            CreateElement::NAMESPACEWORD . ':tblStylePr>';
    }

    /**
     * Generate w:tblPr
     *
     * @access protected
     */
    protected function generateTBLPR()
    {
        $this->_xml = str_replace(
            '__GENERATESTYLE__', '<' .
            CreateElement::NAMESPACEWORD .
            ':tblPr></' . CreateElement::NAMESPACEWORD .
            ':tblPr>__GENERATESTYLE__',
            $this->_xml
        );
    }

    /**
     * Generate w:tcPr
     *
     * @access protected
     */
    protected function generateTCPR()
    {
        $this->_xml = str_replace(
            '__GENERATESTYLE__', '<' .
            CreateElement::NAMESPACEWORD .
            ':tcPr>__GENERATETBLPR__</' . CreateElement::NAMESPACEWORD .
            ':tcPr>__GENERATESTYLE__',
            $this->_xml
        );
    }

    /**
     * Generate w:tcBorders
     *
     * @access protected
     */
    protected function generateTCBORDERS()
    {
        $this->_xml = str_replace(
            '__GENERATETBLPR__', '<' .
            CreateElement::NAMESPACEWORD .
            ':tcBorders>__GENERATETBLBORDERS__</' .
            CreateElement::NAMESPACEWORD . ':tcBorders>__GENERATETBLPR__',
            $this->_xml
        );
    }

    /**
     * Generate w:shd
     *
     * @access protected
     * @param string $val
     * @param string $color
     * @param string $fill
     * @param string $themeFill
     * @param string $themeFillTint
     */
    protected function generateSHD($val, $color = '', $fill = '',
                                   $themeFill = '', $themeFillTint = '')
    {
        $xmlAux = '<' . CreateElement::NAMESPACEWORD . ':shd ' .
            CreateElement::NAMESPACEWORD . ':val="' . $val . '"';
        if ($color != '')
            $xmlAux .= ' ' . CreateElement::NAMESPACEWORD .
                ':color="' . $color . '"';
        if ($fill != '')
            $xmlAux .= ' ' . CreateElement::NAMESPACEWORD .
                ':fill="' . $fill . '"';
        if ($themeFill != '')
            $xmlAux .= ' ' . CreateElement::NAMESPACEWORD .
                ':themeFill="' . $themeFill . '"';
        if ($themeFillTint != '')
            $xmlAux .= ' ' . CreateElement::NAMESPACEWORD .
                ':themeFillTint="' . $themeFillTint . '"';
        $xmlAux .= '></' . CreateElement::NAMESPACEWORD .
            ':shd>__GENERATETBLPR__';
        $this->_xml = str_replace('__GENERATETBLPR__', $xmlAux, $this->_xml);
    }

}