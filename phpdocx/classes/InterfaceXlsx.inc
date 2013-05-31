<?php

/**
 * Interface for xlsx
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
interface InterfaceXlsx {
	/**
     * Create a excel sheet
     *
     * @access public
     */
    public function createExcelSheet($dats);

    /**
     * Create a shared string file from the xlsx
     *
     * @access public
     */
    public function createExcelSharedStrings($dats);

    /**
     * return a table file from the xlsx
     *
     * @access public
     */
    public function createExcelTable($dats);
}