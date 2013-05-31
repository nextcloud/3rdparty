<?php

/**
 * Insert a link into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addLink('Link to Google', array('url'=> 'http://www.google.es', 'font' => 'Arial', 'color' => 'blue', 'u' => 'single'));

$docx->createDocx('../docx/example_link');