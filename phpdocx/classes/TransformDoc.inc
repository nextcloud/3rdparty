<?php

/**
 * Transform DOCX to PDF or XHTML
 *
 * @category   Phpdocx
 * @package    transform
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */

error_reporting(E_ALL & ~E_NOTICE);

require_once dirname(__FILE__) . '/AutoLoader.inc';
AutoLoader::load();

class TransformDoc
{
    const SCHEMA_IMAGEDOCUMENT =
    'http://schemas.openxmlformats.org/officeDocument/2006/relationships/image';
    const SCHEMA_OFFICEDOCUMENT =
    'http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument';

    /**
     *
     * @access private
     * @var string
     */
    private $_document;

    /**
     *
     * @access private
     * @var array
     */
    private $_docProps;

    /**
     *
     * @access private
     * @var string
     */
    private $_xhtml;

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
     * Getter. Document
     *
     * @access public
     */
    public function getDocument()
    {
        return $this->_document;
    }

    /**
     * Getter. Document
     *
     * @access public
     */
    public function setDocument($document)
    {
        $this->_document = $document;
    }

    /**
     * Getter. DocProps
     *
     * @access public
     */
    public function getDocProps()
    {
        return $this->_docProps;
    }

    /**
     * Getter. DocProps
     *
     * @access public
     */
    public function setDocProps($props)
    {
        $this->_docProps = $props;
    }

    /**
     * Getter. File
     *
     * @access public
     */
    public function getstrFile()
    {
        return $this->strFile;
    }

    /**
     * Getter. XHTML
     *
     * @access public
     */
    public function getStrXHTML()
    {
        return $this->_xhtml;
    }

    /**
     * Getter. Output file
     *
     * @access public
     */
    public function getStrOutputFile()
    {
        return $this->strOutputFile;
    }

    /**
     * Setter. File
     *
     * @access public
     */
    public function setstrFile($file)
    {
        $this->strFile = $file;
    }

    /**
     * Setter. XHTML
     *
     * @access public
     */
    public function setStrXHTML($strXHTML)
    {
        $this->_xhtml = $strXHTML;
    }

    /**
     *
     * @param string $outputFile
     */
    public function setStrOutputFile($outputFile)
    {
        $this->strOutputFile = $outputFile;
    }

    /**
     * Return zip path
     *
     * @access public
     * @return string
     */
    public function absoluteZipPath($path)
    {
        $path = str_replace(array('/', '\\'), DIRECTORY_SEPARATOR, $path);
        $parts = array_filter(
            explode(DIRECTORY_SEPARATOR, $path), 'strlen'
        );
        $arrAbsolutes = array();
        foreach ($parts as $datParts) {
            if ('.' == $datParts)
                continue;
            if ('..' == $datParts) {
                array_pop($arrAbsolutes);
            } else {
                $arrAbsolutes[] = $datParts;
            }
        }
        return implode('/', $arrAbsolutes);
    }

    /**
     * Clean HTML
     *
     * @access public
     */
    public function cleanXHTML()
    {
        $sectionOne = explode('<head>', $this->_xhtml);
        $sectionTwo = explode('</head>', $this->_xhtml);
        $sectionTwo = str_replace(
            'src="?image="', 'src="imagen_not_found.jpg"', $sectionTwo
        );
        if (!isset($sectionTwo[1])) {
            $sectionTwo[1] = $this->_xhtml;
            $sectionOne[0] = '';
        }
        $this->_xhtml = $sectionOne[0] .
            '<head><meta http-equiv="Content-Type" ' .
            'content="text/html; charset=utf-8" /></head>' . $sectionTwo[1];
    }

    /**
     * Return file name
     *
     * @access public
     */
    public function getFileName()
    {
        try {
            $partsFile = explode('/', $this->strFile);
            $divideFile = explode('.', array_pop($partsFile));
            $fileName = array_shift($divideFile);
        }
        catch (Exception $e) {
            $fileName = 'file';
        }
        return $fileName;
    }

    /**
     * Convert DOCX to XHTML
     *
     * @access public
     */
    public function generateXHTML()
    {
        $package = new ZipArchive();
        if (!$package->open($this->strFile)) {
            echo 'Unable to find the DOCX file';
            exit();
        }
        $relations = simplexml_load_string(
            $package->getFromName('_rels/.rels')
        );

        foreach ($relations->Relationship as $rel) {
            if ($rel["Type"] == TransformDoc::SCHEMA_OFFICEDOCUMENT) {
                $xml = $package->getFromName(
                    $this->absoluteZipPath(
                        dirname($rel['Target']) . '/' .
                        basename($rel['Target'])
                    )
                );
                $this->setDocument($xml);
                $xmlDOM = new DOMDocument();
                $xml = str_replace('</w:wordDocument>', '', $xml);
                $xml = preg_replace(
                    '/(<w:wordDocument)+(.)*(><w:body>)/', '<w:body>', $xml
                );
                @$xmlDOM->loadXML($xml);
                $xsl = new DOMDocument();
                $xsl->load(dirname(__FILE__) . '/../xsl/docx2html.xsl');

                $xsltProc = new XSLTProcessor();
                
                $xsltProc->importStylesheet($xsl);
                $this->_xhtml = $xsltProc->transformToXML($xmlDOM);
            }
        }

        $pattern = "'src\s*=\s*([\"\'])?(?(1) (.*?)\\1 | ([^\s\>]+))'isx";
        preg_match_all($pattern, $this->_xhtml, $domImgs);

        $idImgs = array();
        foreach ($domImgs[0] as $dats) {
            $datsFiltered = explode('"', $dats);
            if (preg_match('/^\?image=rId/', $datsFiltered[1])) {
                $datFiltered = explode('?image=', $dats);
                $idImgs[] = substr($datFiltered[1], 0, -1);
            }
        }
        $relationsImgs = simplexml_load_string(
            $package->getFromName('word/_rels/document.xml.rels')
        );
        $pathImgs = array();
        foreach ($relationsImgs->Relationship as $relImg) {
            if ($relImg["Type"] == TransformDoc::SCHEMA_IMAGEDOCUMENT) {
                $pathImgs[(string) $relImg["Id"]] =
                    (string) $relImg["Target"];
                $pathZip[] = 'word/' . (string) $relImg["Target"];
            }
        }

        foreach ($idImgs as $datsIdImgs) {
            $this->_xhtml = str_replace(
                "src=\"?image=$datsIdImgs\"",
                "src=\"files/files_" .
                "$this->strFile/media/word/$pathImgs[$datsIdImgs]\"",
                $this->_xhtml
            );
        }

        if (!empty($pathZip)) {
            $package->extractTo(
                "files/files_$this->strFile/media", $pathZip
            );
            $package->close();
        }
    }

    /**
     * Convert DOCX to PDF, using dompdf. DOCX->XHTML->PDF
     *
     * @access public
     */
    public function generatePDF($path = '')
    {
        $this->generateXHTML();
        $this->cleanXHTML();
        $this->_extractProps();
        try {
            $domPDF = new DOMPDF();
            $domPDF->load_html($this->_xhtml);
            $docProps = $this->getDocProps();
            $domPDF->set_paper($docProps['size'], $docProps['orientation']);
            $domPDF->render();
            $fileName = $this->getFileName() . '.pdf';
            if($path == ''){
                $domPDF->stream($fileName);
            }else{
                file_put_contents($path, $domPDF->output()); 
            }
        }
        catch (Exception $err) {
            echo 'Unable to generate PDF file. ';
            echo $err;
        }
    }

    /**
     * Validate HTML using tidy
     *
     * @access public
     */
    public function validatorXHTML()
    {
        ob_start();
        echo $this->_xhtml;
        $html = ob_get_clean();
        $config = array(
            'indent' => true,
            'output-xhtml' => true,
            'wrap' => 200);
        $tidy = new tidy();
        $tidy->parseString($html, $config, 'utf8');
        $tidy->cleanRepair();
        $this->_xhtml = $tidy;
    }

    /**
     * Get the document properties
     *
     * @return array
     */
    private function _extractProps()
    {
        $xmlDOM = new DOMDocument();
        $xmlDOM->loadXML($this->getDocument());
        //Get the page size and orientation
        $node = $xmlDOM->getElementsByTagName('pgSz');
        $docProps = array();
        $width = number_format(
                $node->item(0)->getAttribute('w:w') / 20,
                2, '.', '');
        $height = number_format(
                $node->item(0)->getAttribute('w:h') / 20,
                2, '.', '');
        $orient = $node->item(0)->getAttribute('w:orient');
        if (empty($orient) || $orient == 'portrait') {
            $docProps['orientation'] = 'portrait';
            $docProps['size'] = array(0, 0, $width, $height);
        } else {
            $docProps['orientation'] = 'landscape';
            $docProps['size'] = array(0, 0, $height, $width);
        }

        //Get the page margins
        $node = $xmlDOM->getElementsByTagName('pgMar');
        $margin = 'margin: ' .
                floor($node->item(0)->getAttribute('w:top') / 15) . 'px ' .
                floor($node->item(0)->getAttribute('w:right') / 15) . 'px ' .
                floor($node->item(0)->getAttribute('w:bottom') / 15) . 'px ' .
                floor($node->item(0)->getAttribute('w:left') / 15) . 'px;';
        $xml = str_replace('$MARGIN$', $margin, $this->getStrXHTML());
        $this->setStrXHTML($xml);
        
        $this->setDocProps($docProps);
    }

}