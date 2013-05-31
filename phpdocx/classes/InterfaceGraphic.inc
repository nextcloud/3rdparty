<?php

/**
 * Interface for charts
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
interface InterfaceGraphic {
	/**
     * Create embedded xml chart
     *
     * @access public
     */
    public function createEmbeddedXmlChart();

    /**
     * return the tags where the data is written
     *
     * @access public
     */
    public function dataTag();

    /**
     * return the object type of the xlsx
     *
     * @access public
     */
    public function getXlsxType();
}