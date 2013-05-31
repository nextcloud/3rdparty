<?php

/**
 * Transform DOCX to Text.
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

$docx->docx2txt('../files/Text.docx', '../docx/text.txt');