<?php

/**
 * Sets the default language of the document.
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

$docx->setLanguage('es-ES');

$docx->AddText('Este documento tiene el español de España como idioma por defecto (The default document language has been set to Spanish-Spain).');

$docx->createDocx('../docx/example_setLanguage');