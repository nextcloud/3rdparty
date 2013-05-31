<?php

/**
 * WordML
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
include_once dirname(__FILE__) . '/CreateElement.inc';

class WordML extends CreateElement
{
    
    /**
     *
     * @access private
     * @var string
     */
    private $_wordML;
    /**
     *
     * @access private
     * @var string
     */
    private static $_instance = NULL;
    
     /**
     *
     * @access public
     * @static
     * @var Logger
     */
    public static $log;
    
    
    /**
     * Construct
     *
     * @access public
     */
    public function __construct()
    {
        $this->_debug = Debug::getInstance();
        Logger::configure(dirname(__FILE__) . '/conf/log4php.properties');
        self::$log = Logger::getLogger('phpdocx_logger');
    }

    /**
     * Destruct
     *
     * @access public
     */
    public function __destruct()
    {

    }

    /**
     * Magic method, returns current XML
     *
     * @access public
     * @return string Return current XML
     */
    public function __toString()
    {
        return $this->_wordML;
    }


    /**
     * Create raw WordML
     *
     * @access public
     * @param string $data
     */
    public function createRawWordML($data)
    {
        $this->_wordML = (string) $data;
    }
    
    /**
     * returns only the runs of content for embedding
     *
     * @access public
     * @param string $data
     */
    public function inlineWordML()
    {
        $wordMLChunk = new DOMDocument();
        $namespaces = 'xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships" xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:office:word" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml" ';
        $wordML = '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?><w:root '.$namespaces.'>'.$this->_wordML;
        $wordML = $wordML.'</w:root>';
        $wordMLChunk->loadXML($wordML);
        $wordMLXpath = new DOMXPath($wordMLChunk);
        $wordMLXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $query= '//w:r';
        $wrNodes = $wordMLXpath->query($query); 
        $blockCleaned = '';
        foreach ($wrNodes as $node){
           $nodeR = $node->ownerDocument->saveXML($node);       
           $blockCleaned .= $nodeR;
        }
        
        return $blockCleaned;
    }

    
}
