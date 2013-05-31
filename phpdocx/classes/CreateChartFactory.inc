<?php

/**
 * Chart factory
 *
 * @category   Phpdocx
 * @package    charts
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
class CreateChartFactory
{

    /**
     * Create an object
     *
     * @access public
     * @param string $type Object type
     * @return mixed
     * @static
     */
    public static function createObject($type)
    {
        $type = substr($type, 0, strpos($type, 'Chart') + 5);
        $type = str_replace('3D', '', $type);
        $type = 'Create' . ucwords($type);
        $type = str_replace('Col', 'Bar', $type);
        return new $type();
        
    }
}
