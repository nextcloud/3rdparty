<?php

/**
 * Logger
 *
 * @category   Phpdocx
 * @package    logger
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */

class PhpdocxLogger
{
    /**
     *
     * @access private
     * @static
     * @var string
     */
    private static $_log = NULL;

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @param $message Message to send to logging framework
     * @param $level Allowed values: trace, debug, info, warn, error, fatal
     * @static
     */
    public static function logger($message, $level)
    {
        $levels = array(
            'debug', 
            'info', 
            'notice', 
            'warning', 
            'error', 
            'fatal',
        );

        if (!self::$_log) {
            Logger::configure(dirname(__FILE__) . '/../config/log4php.xml');
            self::$_log = Logger::getLogger('phpdocx_logger');
        }

        // only some levels are valid
        if (in_array($level, $levels)) {
            $stringLevel = strtolower($level);
            self::$_log->info($message);

            // stop phpdocx if fatal level
            if ($level == 'fatal') {
                throw new Exception($message);
            }
        }
    }
}