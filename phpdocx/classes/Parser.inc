<?php

/**
 * Parse DOCX file
 *
 * @category   Phpdocx
 * @package    parser
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
class Parser
{

    /**
     *
     * @access private
     * @var string
     */
    private static $_instance = NULL;

    /**
     *
     * @access private
     * @var array
     */
    private $_xml = array();
    
    /**
     * Construct
     *
     * @access private
     */
    private function __construct()
    {
        
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
        return $this->_xml;
    }

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @return CreateText
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new Parser();
        }
        return self::$_instance;
    }

    /**
     * Getter. XHTML
     *
     * @access public
     */
    public function getXML()
    {
        return $this->_xml;
    }

    /**
     * Read DOCX file and extract WordML content
     * 
     * @access public
     * @param  $path File path
     */
    public function readFile($path)
    {
        if (file_exists($path)) {
            // open DOCX file
            $docx = new ZipArchive();
            $docx->open($path);
            // read all files and add them to xml array
            for ($i = 0; $i < $docx->numFiles; $i++) {
                $stat = $docx->statIndex($i);
                $this->_xml[$stat['name']] = new SimpleXMLElement($docx->getFromName($stat['name']));
            }
            // close DOCX file
            $docx->close();
        } else {
            throw new Exception('File does not exist');
        }
    }

}
