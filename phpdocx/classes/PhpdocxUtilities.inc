<?php

/**
 * PhpdocxUtilities
 *
 * @category   Phpdocx
 * @package    utilities
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */

class PhpdocxUtilities
{
    /**
     *
     * @access public
     * @static
     * @var integer
     */
    private static $_phpdocxConfig;

    /**
     * Check if string is UTF8
     * 
     * @access public
     * @param string $string String to check
     * @static
     * @return boolean
     */
    public static function isUtf8($string_input)
    {
        $string = $string_input;

        $string = preg_replace("#[\x09\x0A\x0D\x20-\x7E]#", "", $string);
        $string = preg_replace("#[\xC2-\xDF][\x80-\xBF]#", "", $string);
        $string = preg_replace("#\xE0[\xA0-\xBF][\x80-\xBF]#", "", $string);
        $string = preg_replace("#[\xE1-\xEC\xEE\xEF][\x80-\xBF]{2}#", "", $string);
        $string = preg_replace("#\xED[\x80-\x9F][\x80-\xBF]#", "", $string);
        $string = preg_replace("#\xF0[\x90-\xBF][\x80-\xBF]{2}#", "", $string);
        $string = preg_replace("#[\xF1-\xF3][\x80-\xBF]{3}#", "", $string);
        $string = preg_replace("#\xF4[\x80-\x8F][\x80-\xBF]{2}#", "", $string);

        return ($string == ""?true:false); 

    }

    /**
     * Return a uniqueid to be used in tags
     *
     * @access public
     * @static
     * @return string
     */
    public static function parseConfig()
    {
        if (!isset(self::$_phpdocxConfig)) {
            self::$_phpdocxConfig = parse_ini_file(dirname(__FILE__) . '/../config/phpdocxconfig.ini', true);
        }
        return self::$_phpdocxConfig;
    }

    /**
     * Return a uniqueid to be used in tags
     *
     * @access public
     * @static
     * @return string
     */
    public static function uniqueId()
    {
        $uniqueid = uniqid('phpdocx_');

        return $uniqueid;
    }
}