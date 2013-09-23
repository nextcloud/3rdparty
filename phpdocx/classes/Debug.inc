<?php

/**
 * Debug generated XML
 *
 * @category   Phpdocx
 * @package    debug
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
class Debug
{

    /**
     *
     * @access private
     * @var int
     */
    private $_active;
    /**
     *
     * @access private
     * @static
     * @var string
     */
    private static $_instance = null;
    /**
     *
     * @access private
     * @var array
     */
    private $_messages;
    /**
     *
     * @access private
     * @var string
     */
    private $_templateMessage;

    /**
     * Construct
     *
     * @access public
     */
    public function __construct()
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
     * Magic method, returns error messages
     *
     * @access public
     * @return string Return found errors using a template
     */
    public function __toString()
    {
        if ($this->_active) {
            $this->generateTemplate();
            return $this->_templateMessage;
        }
    }

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @return Debug
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new Debug();
        }
        return self::$_instance;
    }

    /**
     * Setter. Access to messages var
     *
     * @access public
     * @param array $messages
     */
    public function setMessages($messages)
    {
        $this->_messages = $messages;
    }

    /**
     * Getter. Access to messages var
     *
     * @access public
     * @return array
     */
    public function getMessages()
    {
        return $this->_messages;
    }

    /**
     * Setter. Enable debug
     *
     * @access public
     * @param int $active
     */
    public function setActive($active)
    {
        $this->_active = $active;
    }

    /**
     * Getter. Return debug status
     *
     * @access public
     * @return int
     */
    public function getActive()
    {
        return $this->_active;
    }

    /**
     * Add a new mesagge to the pool of _messages
     *
     * @access public
     * @param mixed $message
     */
    public function addMessage($message)
    {
        $this->_messages[] = $message;
    }

    /**
     * Enable debug
     *
     * @access public
     * @deprecated deprecated since version 2.0
     */
    public function enableDebug()
    {
        $this->_messages = array();
        $this->setActive(1);
    }

    /**
     * Disable debug
     *
     * @access public
     * @deprecated deprecated since version 2.0
     */
    public function fDisableDebug()
    {
        $this->setActive(0);
    }

    /**
     * Assign template to use
     *
     * @access protected
     * @deprecated deprecated since version 2.0
     */
    protected function generateTemplate()
    {
        $this->_templateMessage = '<html xmlns="http://www.w3.org/1999/xhtml"'
                . 'xml:lang="es" lang="es"><head></head><body><ul>';
        foreach ($this->_messages as $dat) {
            if (is_array($dat)) {
                foreach ($this->_messages as $unkDatArr) {
                    if (is_array($unkDatArr)) {
                        foreach ($unkDatArr as $xmlErrorDat) {
                            $this->_templateMessage .= '<li>'
                                    . $xmlErrorDat->message . '</li>';
                        }
                    } else {
                        $this->_templateMessage .= '<li>' . $unkDatArr
                                . '</li>';
                    }
                }
            } else {
                $this->_templateMessage .= '<li>' . $dat . '</li>';
            }
        }
        $this->_templateMessage .= '</ul></body></html>';
    }

}
