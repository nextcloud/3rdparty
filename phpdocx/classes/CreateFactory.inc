<?php

/**
 * Simple factory
 *
 * @category   Phpdocx
 * @package    factory
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
class CreateFactory
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
        return new $type();
    }

}
