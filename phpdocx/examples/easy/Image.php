<?php

/**
 * Insert an image into a Word document.
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

$paramsImg = array(
    'name' => '../files/img/image.png',
    'scaling' => 50,
    'spacingTop' => 100,
    'spacingBottom' => 100,
    'spacingLeft' => 100,
    'spacingRight' => 100,
    'textWrap' => 1,
    'border' => 1,
    'borderDiscontinuous' => 1
);

$docx->addImage($paramsImg);

$docx->createDocx('../docx/example_image');