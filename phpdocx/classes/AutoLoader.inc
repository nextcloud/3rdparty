<?php

/**
 * Autoloader
 *
 * @category   Phpdocx
 * @package    loader
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
class AutoLoader
{

    /**
     * Main tags of relationships XML
     *
     * @access public
     * @static
     */
    public static function load()
    {
        spl_autoload_register(array('AutoLoader', 'autoloadGenericClasses'));
        spl_autoload_register(array('AutoLoader', 'autoloadPhpdocx'));
        spl_autoload_register(array('AutoLoader', 'autoloadLog4php'));
        spl_autoload_register(array('AutoLoader', 'autoloadTcpdf'));
        spl_autoload_register(array('AutoLoader', 'autoloadPdf'));
        spl_autoload_register(array('AutoLoader', 'autoloadDompdf'));
        spl_autoload_register(array('AutoLoader', 'autoloadMht'));
    }

    /**
     * Autoload dompdf
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadDompdf($className)
    {
        $pathDompdf = dirname(__FILE__) . '/../pdf/dompdf_config.inc.php';
        if (file_exists($pathDompdf)) {
            require_once $pathDompdf;
        }
    }

    /**
     * Autoload phpdocx
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadGenericClasses($className)
    {
        $pathPhpdocx = dirname(__FILE__) . '/' . $className . '.inc';
        if (file_exists($pathPhpdocx)) {
            require_once $pathPhpdocx;
        }
    }

    /**
     * Autoload log4php
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadLog4php($className)
    {
        $pathLogphp = dirname(__FILE__) . '/../lib/log4php/'
            . $className . '.php';
        if (file_exists($pathLogphp)) {
            require_once $pathLogphp;
        }
    }

    /**
     * Autoload mht
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadMht($className)
    {
        $pathMht = dirname(__FILE__) . '/../lib/'
            . $className . '.php';
        if (file_exists($pathMht)) {
            require_once $pathMht;
        }
    }

    /**
     * Autoload phpdocx
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadPdf($className)
    {
        $pathPDF = dirname(__FILE__) . '/pdf/' . $className . '.inc';
        if (file_exists($pathPDF)) {
            require_once $pathPDF;
        }
        $pathTCPDF = dirname(__FILE__) . '/../pdf/tcpdf/tcpdf.php';
        if (file_exists($pathTCPDF)) {
            require_once $pathTCPDF;
        }
        $pathFPDI = dirname(__FILE__) . '/../lib/fpdi/fpdi.php';
        if (file_exists($pathFPDI)) {
            require_once $pathFPDI;
        }
    }

    /**
     * Autoload phpdocx
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadPhpdocx($className)
    {
        $pathPhpdocx = dirname(__FILE__) . '/docx/' . $className . '.inc';
        if (file_exists($pathPhpdocx)) {
            require_once $pathPhpdocx;
        }
    }

    /**
     * Autoload Tcpdf
     *
     * @access public
     * @param string $className Class to load
     */
    public static function autoloadTcpdf($className)
    {
        $pathTcpdf = dirname(__FILE__) . '/../pdf/class.tcpdf.php';
        if (file_exists($pathTcpdf)) {
            require_once $pathTcpdf;
        }
    }

}
