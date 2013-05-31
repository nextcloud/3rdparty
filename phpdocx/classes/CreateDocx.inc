<?php

/**
 * Generate a DOCX file
 *
 * @category   Phpdocx
 * @package    create
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */

error_reporting(E_ALL & ~E_STRICT & ~E_NOTICE);
require_once dirname(__FILE__) . '/AutoLoader.inc';
AutoLoader::load();
require_once dirname(__FILE__) . '/Phpdocx_config.inc';

class CreateDocx extends CreateDocument
{
    const NAMESPACEWORD = 'w';
    const SCHEMA_IMAGEDOCUMENT =
    'http://schemas.openxmlformats.org/officeDocument/2006/relationships/image';
    const SCHEMA_OFFICEDOCUMENT =
    'http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument';

    /**
     *
     * @var string
     * @access public
     * @static
     */
    public static $PHPDOCXStyles;
    /**
     *
     * @access public
     * @static
     * @var integer
     */
    public static $numUL;
    /**
     *
     * @access public
     * @var integer
     */
    public static $numOL;
    /**
     *
     * @var string
     * @access public
     * @static
     */
    public static $orderedListStyle;
    /**
     *
     * @var string
     * @access public
     * @static
     */
    public static $unorderedListStyle;
    /**
     *
     * @access public
     * @var array
     */
    public $fileGraphicTemplate;
    /**
     *
     * @access private
     * @var boolean
     */
    private $footerAdded;
    /**
     *
     * @access private
     * @var boolean
     */
    private $headerAdded;
    /**
     *
     * @access public
     * @var string
     */
    public $graphicTemplate;
    /**
     *
     * @access public
     * @static
     * @var int
     */
    public static $intIdWord;
    /**
     *
     * @access public
     * @static
     * @var Logger
     */
    public static $log;
    /**
     *
     * @access public
     * @static
     * @var array
     */
     public static $settings = array('w:writeProtection',
                                    'w:view',
                                    'w:zoom',
                                    'w:removePersonalInformation',
                                    'w:removeDateAndTime',
                                    'w:doNotDisplayPageBoundaries',
                                    'w:displayBackgroundShape',
                                    'w:printPostScriptOverText',
                                    'w:printFractionalCharacterWidth',
                                    'w:printFormsData',
                                    'w:embedTrueTypeFonts',
                                    'w:embedSystemFonts',
                                    'w:saveSubsetFonts',
                                    'w:saveFormsData',
                                    'w:mirrorMargins',
                                    'w:alignBordersAndEdges',
                                    'w:bordersDoNotSurroundHeader',
                                    'w:bordersDoNotSurroundFooter',
                                    'w:gutterAtTop',
                                    'w:hideSpellingErrors',
                                    'w:hideGrammaticalErrors',
                                    'w:activeWritingStyle',
                                    'w:proofState',
                                    'w:formsDesign',
                                    'w:attachedTemplate',
                                    'w:linkStyles',
                                    'w:stylePaneFormatFilter',
                                    'w:stylePaneSortMethod',
                                    'w:documentType',
                                    'w:mailMerge',
                                    'w:revisionView',
                                    'w:trackRevisions',
                                    'w:doNotTrackMoves',
                                    'w:doNotTrackFormatting',
                                    'w:documentProtection',
                                    'w:autoFormatOverride',
                                    'w:styleLockTheme',
                                    'w:styleLockQFSet',
                                    'w:defaultTabStop',
                                    'w:autoHyphenation',
                                    'w:consecutiveHyphenLimit',
                                    'w:hyphenationZone',
                                    'w:doNotHyphenateCaps',
                                    'w:showEnvelope',
                                    'w:summaryLength',
                                    'w:clickAndTypeStyle',
                                    'w:defaultTableStyle',
                                    'w:evenAndOddHeaders',
                                    'w:bookFoldRevPrinting',
                                    'w:bookFoldPrinting',
                                    'w:bookFoldPrintingSheets',
                                    'w:drawingGridHorizontalSpacing',
                                    'w:drawingGridVerticalSpacing',
                                    'w:displayHorizontalDrawingGridEvery',
                                    'w:displayVerticalDrawingGridEvery',
                                    'w:doNotUseMarginsForDrawingGridOrigin',
                                    'w:drawingGridHorizontalOrigin',
                                    'w:drawingGridVerticalOrigin',
                                    'w:doNotShadeFormData',
                                    'w:noPunctuationKerning',
                                    'w:characterSpacingControl',
                                    'w:printTwoOnOne',
                                    'w:strictFirstAndLastChars',
                                    'w:noLineBreaksAfter',
                                    'w:noLineBreaksBefore',
                                    'w:savePreviewPicture',
                                    'w:doNotValidateAgainstSchema',
                                    'w:saveInvalidXml',
                                    'w:ignoreMixedContent',
                                    'w:alwaysShowPlaceholderText',
                                    'w:doNotDemarcateInvalidXml',
                                    'w:saveXmlDataOnly',
                                    'w:useXSLTWhenSaving',
                                    'w:saveThroughXslt',
                                    'w:showXMLTags',
                                    'w:alwaysMergeEmptyNamespace',
                                    'w:updateFields',
                                    'w:hdrShapeDefaults',
                                    'w:footnotePr',
                                    'w:endnotePr',
                                    'w:compat',
                                    'w:docVars',
                                    'w:rsids',
                                    'm:mathPr',
                                    'w:uiCompat97To2003',
                                    'w:attachedSchema',
                                    'w:themeFontLang',
                                    'w:clrSchemeMapping',
                                    'w:doNotIncludeSubdocsInStats',
                                    'w:doNotAutoCompressPictures',
                                    'w:forceUpgrade',
                                    'w:captions',
                                    'w:readModeInkLockDown',
                                    'w:smartTagType',
                                    'sl:schemaLibrary',
                                    'w:shapeDefaults',
                                    'w:doNotEmbedSmartTags',
                                    'w:decimalSymbol',
                                    'w:listSeparator'
                                    );
    /**
     *
     * @access private
     * @var string
     */
    private $_background;
     /**
     *
     * @access private
     * @var string
     */
    private $_backgroundColor;
     /**
     *
     * @access private
     * @var string
     */
    private $_baseTemplateFilesPath;
   /**
     *
     * @access private
     * @var string
     */
    private $_baseTemplatePath;
   /**
     *
     * @access private
     * @var string
     */
    private $_baseTemplateZip;
    /**
     *
     * @access private
     * @var array
     */
    private $_bookmarksIds;
   /**
     *
     * @access private
     * @var boolean
     */
    private $_compatibilityMode;
    /**
     *
     * @access private
     * @var string
     */
    private $_contentTypeC;
    /**
     *
     * @access private
     * @var string
     */
    private $_defaultFont;
    /**
     *
     * @access private
     * @var Debug
     */
    private $_debug;
    /**
     *
     * @access private
     * @var array
     */
    private $_defaultPHPDOCXStyles;
    /**
     *
     * @access private
     * @var boolean
     */
    private $_defaultTemplate;
    /**
     *
     * @access private
     * @var boolean
     */
    private $_docm;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsAppC;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsAppT;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCoreC;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCoreT;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCustomC;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCustomT;
    /**
     *
     * @access private
     * @var string
     */
    private static $_encodeUTF;
    /**
     *
     * @access private
     * @var string
     */
    private $_extension;
    /**
     *
     * @access private
     * @var int
     */
    private $_idImgHeader;
    /**
     *
     * @access private
     * @var int
     */
    private $_idRels;
    /**
     *
     * @access private
     * @var array
     */
    private $_idWords;
    /**
     *
     * @access private
     * @var string
     */
    private $_language;
    /**
     *
     * @access private
     * @var boolean
     */
    private $_macro;
    /**
     *
     * @access private
     * @var int
     */
    private $_markAsFinal;
    /**
     *
     * @access private
     * @var array
     */
    private $_parsedStyles;
    /**
     *
     * @access private
     * @var array
     */
    private $_phpdocxconfig;
    /**
     *
     * @access private
     * @var string
     */
    private $_relsRelsC;
    /**
     *
     * @access private
     * @var string
     */
    private $_relsRelsT;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeader;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeaderFooterImage;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeaderFooterImageExternal;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeaderFooterLink;
     /**
     *
     * @access private
     * @var array
     */
    private $_relsFooter;
     /**
     *
     * @access private
     * @var string
     */
    private $_sectPr;
    /**
     * Directory path used for temporary files
     *
     * @access private
     * @var string
     */
    private $_tempDir;
    /**
     * Path of temp file to use as DOCX file
     *
     * @access private
     * @var string
     */
    private $_tempFile;
    /**
     * Paths of temps files to use as DOCX file
     *
     * @access private
     * @var array
     */
    private $_tempFileXLSX;
    /**
     * Numberings used by the replaceTemplateVariabeByHTML
     *
     * @access private
     * @var array
     */
    private $_templateNumberings;
    /**
     * Unique id for the insertion of new elements
     *
     * @access private
     * @var string
     */
    private $_uniqid;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordDocumentC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordDocumentT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordDocumentStyles;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordEndnotesC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordEndnotesT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFontTableC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFontTableT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordFooterC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordFooterT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFootnotesC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFootnotesT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordHeaderC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordHeaderT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordNumberingC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordNumberingT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordRelsDocumentRelsC;
    /**
     *
     * @access private
     * @var DOMDocument
     */
    private $_wordRelsDocumentRelsT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsFooterRelsC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsFooterRelsT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsHeaderRelsC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsHeaderRelsT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordSettingsC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordSettingsT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordStylesC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordStylesT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordThemeThemeT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordThemeThemeC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordWebSettingsC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordWebSettingsT;
    /**
     *
     * @access private
     * @var ZipArchive
     */
    private $_zipDocx;

    /**
     * Construct
     *
     * @access public
     * @param string $baseTemplatePath. Optional, basicTemplate.docx as default
     */
    public function __construct($baseTemplatePath = PHPDOCX_BASE_TEMPLATE)
    {
        $this->_debug = Debug::getInstance();

        $this->_phpdocxconfig = PhpdocxUtilities::parseConfig();

        $this->_background = '';
        $this->_backgroundColor = 'FFFFFF';
        $this->_baseTemplateFilesPath;
        if ($baseTemplatePath == 'docm') {
            $this->_baseTemplatePath = PHPDOCX_BASE_FOLDER.'phpdocxBaseTemplate.docm';
            $this->_docm = true;
            $this->_defaultTemplate = true;
            $this->_extension = 'docm';
        } else if($baseTemplatePath == 'docx') {
            $this->_baseTemplatePath = PHPDOCX_BASE_FOLDER.'phpdocxBaseTemplate.docx';
            $this->_docm = false;
            $this->_defaultTemplate = true;
            $this->_extension = 'docx';
        } else {
            if ($baseTemplatePath == PHPDOCX_BASE_TEMPLATE) {
                $this->_defaultTemplate = true;
            } else {
                $this->_defaultTemplate = false;
            }
            $this->_baseTemplatePath = $baseTemplatePath;
            $extensionArray = explode('.', $this->_baseTemplatePath);
            $extension = array_pop($extensionArray);
            $this->_extension = $extension;
            if ($extension == 'docm') {
                $this->_docm = true;
            } else if ($extension == 'docx') {
                $this->_docm = false;
            } else {
                PhpdocxLogger::logger('Invalid base template extension', 'fatal');
            }
        }
        $this->_baseTemplateZip = new ZipArchive();
        $this->_bookmarksIds = array();
        $this->_idRels = array();
        $this->_idWords = array();
        $this->_idImgHeader = 1;
        $this->_idRels = 1;
        self::$intIdWord = rand(9999999,99999999);
        self::$_encodeUTF = 0;
        $this->_language = 'en-US';
        $this->_markAsFinal = 0;
        $this->graphicTemplate = array();
        $this->fileGraphicTemplate = array();
        $this->_zipDocx = new ZipArchive();
        if ($this->_phpdocxconfig['settings']['temp_path']) {
            $this->_tempDir = $this->_phpdocxconfig['settings']['temp_path'];
        } else {
            $this->_tempDir = self::getTempDir();
        }
        $this->_tempFile = tempnam($this->_tempDir, 'document');
        $this->_templateNumberings;
        $this->_zipDocx->open($this->_tempFile, ZipArchive::OVERWRITE);
        $this->_compatibilityMode = false;
        PhpdocxLogger::logger('Create a temp file to use as initial ZIP file. ' .
            'DOCX is a ZIP file.', 'info');
        // sign is set false as default
        $this->_sign = false;
        $this->_relsRelsC = '';
        $this->_relsRelsT = '';
        $this->_contentTypeC = '';
        $this->_contentTypeT = NULL;
        $this->_defaultFont = '';
        $this->_docPropsAppC = '';
        $this->_docPropsAppT = '';
        $this->_docPropsCoreC = '';
        $this->_docPropsCoreT = '';
        $this->_docPropsCustomC = '';
        $this->_docPropsCustomT = '';
        $this->_macro = 0;
        $this->_relsHeader = array();
        $this->_relsFooter = array();
        $this->_parsedStyles = array();
        $this->_relsHeaderFooterImage = array();
        $this->_relsHeaderFooterImageExternal = array();
        $this->_relsHeaderFooterLink = array();
        $this->_sectPr = NULL;
        $this->_tempFileXLSX = array();
        $this->_uniqid = 'phpdocx_'.uniqid();
        $this->_wordDocumentT = '';
        $this->_wordDocumentC = '';
        $this->_wordDocumentStyles = '';
        $this->_wordEndnotesC = '';
        $this->_wordEndnotesT = '';
        $this->_wordFontTableT = '';
        $this->_wordFontTableC = '';
        $this->_wordFooterC = array();
        $this->_wordFooterT = array();
        $this->_wordFootnotesC = '';
        $this->_wordFootnotesT = '';
        $this->_wordHeaderC = array();
        $this->_wordHeaderT = array();
        $this->_wordNumberingC;
        $this->_wordNumberingT;
        $this->_wordRelsDocumentRelsC = '';
        $this->_wordRelsDocumentRelsT = NULL;
        $this->_wordRelsHeaderRelsC = array();
        $this->_wordRelsHeaderRelsT = array();
        $this->_wordRelsFooterRelsC = array();
        $this->_wordRelsFooterRelsT = array();
        $this->_wordSettingsT = '';
        $this->_wordSettingsC = '';
        $this->_wordStylesT = '';
        $this->_wordStylesC = '';
        $this->_wordThemeThemeT = '';
        $this->_wordThemeThemeC = '';
        $this->_wordWebSettingsT = '';
        $this->_wordWebSettingsC = '';
        $this->_defaultPHPDOCXStyles = array('Default Paragraph Font PHPDOCX', //This is the default paragraph font style used in multiple places
                                            'List Paragraph PHPDOCX', //This is the style used for the defolt ordered and unorderd lists
                                            'Title PHPDOCX', //This style is used by the addTitle method
                                            'Subtitle PHPDOCX', //This style is used by the addTitle method
                                            'Normal Table PHPDOCX', //This style is used for the basic table
                                            'Table Grid PHPDOCX', //This style is for basic tables and is also used to embed HTML tables with border="1"
                                            'footnote text PHPDOCX', //This style is used for default footnotes
                                            'footnote text Car PHPDOCX', //The character style for footnotes
                                            'footnote reference PHPDOCX', // The style for the footnote
                                            'endnote text PHPDOCX', //This style is used for default endnotes
                                            'endnote text Car PHPDOCX', //The character style for endnotes
                                            'endnote reference PHPDOCX'); // The style for the endnote
        //Some variables to control that some v2.4 keep working
        $this->footerAdded = false;
        $this->headerAdded = false;
        self::$PHPDOCXStyles = '<w:styles xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" >
                                        <w:style w:type="character" w:styleId="DefaultParagraphFontPHPDOCX">
                                            <w:name w:val="Default Paragraph Font PHPDOCX"/>
                                            <w:uiPriority w:val="1"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="ListParagraphPHPDOCX">
                                            <w:name w:val="List Paragraph PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:uiPriority w:val="34"/>
                                            <w:qFormat/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:pPr>
                                                <w:ind w:left="720"/>
                                                <w:contextualSpacing/>
                                            </w:pPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="TitlePHPDOCX">
                                            <w:name w:val="Title PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:next w:val="Normal"/>
                                            <w:link w:val="TitleCarPHPDOCX"/>
                                            <w:uiPriority w:val="10"/>
                                            <w:qFormat/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:pPr>
                                                <w:pBdr>
                                                    <w:bottom w:val="single" w:sz="8" w:space="4" w:color="4F81BD" w:themeColor="accent1"/>
                                                </w:pBdr>
                                                <w:spacing w:after="300" w:line="240" w:lineRule="auto"/>
                                                <w:contextualSpacing/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:color w:val="17365D" w:themeColor="text2" w:themeShade="BF"/>
                                                <w:spacing w:val="5"/>
                                                <w:kern w:val="28"/>
                                                <w:sz w:val="52"/>
                                                <w:szCs w:val="52"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="TitleCarPHPDOCX">
                                            <w:name w:val="Title Car PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="TitlePHPDOCX"/>
                                            <w:uiPriority w:val="10"/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:color w:val="17365D" w:themeColor="text2" w:themeShade="BF"/>
                                                <w:spacing w:val="5"/>
                                                <w:kern w:val="28"/>
                                                <w:sz w:val="52"/>
                                                <w:szCs w:val="52"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="SubtitlePHPDOCX">
                                            <w:name w:val="Subtitle PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:next w:val="Normal"/>
                                            <w:link w:val="SubtitleCarPHPDOCX"/>
                                            <w:uiPriority w:val="11"/>
                                            <w:qFormat/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:pPr>
                                                <w:numPr>
                                                    <w:ilvl w:val="1"/>
                                                </w:numPr>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:i/>
                                                <w:iCs/>
                                                <w:color w:val="4F81BD" w:themeColor="accent1"/>
                                                <w:spacing w:val="15"/>
                                                <w:sz w:val="24"/>
                                                <w:szCs w:val="24"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="SubtitleCarPHPDOCX">
                                            <w:name w:val="Subtitle Car PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="SubtitlePHPDOCX"/>
                                            <w:uiPriority w:val="11"/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:i/>
                                                <w:iCs/>
                                                <w:color w:val="4F81BD" w:themeColor="accent1"/>
                                                <w:spacing w:val="15"/>
                                                <w:sz w:val="24"/>
                                                <w:szCs w:val="24"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="table" w:styleId="NormalTablePHPDOCX">
                                            <w:name w:val="Normal Table PHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:qFormat/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:tblPr>
                                                <w:tblInd w:w="0" w:type="dxa"/>
                                                <w:tblCellMar>
                                                    <w:top w:w="0" w:type="dxa"/>
                                                    <w:left w:w="108" w:type="dxa"/>
                                                    <w:bottom w:w="0" w:type="dxa"/>
                                                    <w:right w:w="108" w:type="dxa"/>
                                                </w:tblCellMar>
                                            </w:tblPr>
                                        </w:style>
                                        <w:style w:type="table" w:styleId="TableGridPHPDOCX">
                                            <w:name w:val="Table Grid PHPDOCX"/>
                                            <w:uiPriority w:val="59"/>
                                            <w:rsid w:val="00493A0C"/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:tblPr>
                                                <w:tblInd w:w="0" w:type="dxa"/>
                                                <w:tblBorders>
                                                    <w:top w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:left w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:bottom w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:right w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:insideH w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:insideV w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                </w:tblBorders>
                                                <w:tblCellMar>
                                                    <w:top w:w="0" w:type="dxa"/>
                                                    <w:left w:w="108" w:type="dxa"/>
                                                    <w:bottom w:w="0" w:type="dxa"/>
                                                    <w:right w:w="108" w:type="dxa"/>
                                                </w:tblCellMar>
                                            </w:tblPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="footnoteTextPHPDOCX">
                                            <w:name w:val="footnote Text PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:link w:val="footnoteTextCarPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:rsid w:val="006E0FDA"/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="footnoteTextCarPHPDOCX">
                                            <w:name w:val="footnote Text Car PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="footnoteTextPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:rsid w:val="006E0FDA"/>
                                            <w:rPr>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:styleId="footnoteReferencePHPDOCX">
                                        <w:name w:val="footnote Reference PHPDOCX"/>
                                        <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:unhideWhenUsed/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:rPr>
                                            <w:vertAlign w:val="superscript"/>
                                        </w:rPr>
                                    </w:style>
                                    <w:style w:type="paragraph" w:styleId="endnoteTextPHPDOCX">
                                        <w:name w:val="endnote Text PHPDOCX"/>
                                        <w:basedOn w:val="Normal"/>
                                        <w:link w:val="endnoteTextCarPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:unhideWhenUsed/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:pPr>
                                            <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                        </w:pPr>
                                        <w:rPr>
                                            <w:sz w:val="20"/>
                                            <w:szCs w:val="20"/>
                                        </w:rPr>
                                    </w:style>
                                    <w:style w:type="character" w:customStyle="1" w:styleId="endnoteTextCarPHPDOCX">
                                        <w:name w:val="endnote Text Car PHPDOCX"/>
                                        <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                        <w:link w:val="endnoteTextPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:rPr>
                                            <w:sz w:val="20"/>
                                            <w:szCs w:val="20"/>
                                        </w:rPr>
                                    </w:style>
                                    <w:style w:type="character" w:styleId="endnoteReferencePHPDOCX">
                                        <w:name w:val="endnote Reference PHPDOCX"/>
                                        <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:unhideWhenUsed/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:rPr>
                                            <w:vertAlign w:val="superscript"/>
                                        </w:rPr>
                                    </w:style>
                                 </w:styles>';

          self::$unorderedListStyle = '<w:abstractNum w:abstractNumId="" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" >
                                        <w:multiLevelType w:val="hybridMultilevel"/>
                                        <w:lvl w:ilvl="0" w:tplc="">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="720" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="1" w:tplc="0C0A0003" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val="o"/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="1440" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="2" w:tplc="0C0A0005" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="2160" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="3" w:tplc="0C0A0001" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="2880" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="4" w:tplc="0C0A0003" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val="o"/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="3600" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="5" w:tplc="0C0A0005" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="4320" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="6" w:tplc="0C0A0001" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5040" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="7" w:tplc="0C0A0003" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val="o"/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5760" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="8" w:tplc="0C0A0005" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="6480" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                    </w:abstractNum>';

        self::$orderedListStyle ='<w:abstractNum w:abstractNumId="" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" >
                                        <w:multiLevelType w:val="hybridMultilevel"/>
                                        <w:lvl w:ilvl="0" w:tplc="">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="decimal"/>
                                            <w:lvlText w:val="%1."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="720" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="1" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerLetter"/>
                                            <w:lvlText w:val="%2."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="1440" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="2" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerRoman"/>
                                            <w:lvlText w:val="%3."/>
                                            <w:lvlJc w:val="right"/>
                                            <w:pPr>
                                                <w:ind w:left="2160" w:hanging="180"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="3" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="decimal"/>
                                            <w:lvlText w:val="%4."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="2880" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="4" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerLetter"/>
                                            <w:lvlText w:val="%5."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="3600" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="5" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerRoman"/>
                                            <w:lvlText w:val="%6."/>
                                            <w:lvlJc w:val="right"/>
                                            <w:pPr>
                                                <w:ind w:left="4320" w:hanging="180"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="6" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="decimal"/>
                                            <w:lvlText w:val="%7."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5040" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="7" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerLetter"/>
                                            <w:lvlText w:val="%8."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5760" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="8" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerRoman"/>
                                            <w:lvlText w:val="%9."/>
                                            <w:lvlJc w:val="right"/>
                                            <w:pPr>
                                                <w:ind w:left="6480" w:hanging="180"/>
                                            </w:pPr>
                                        </w:lvl>
                                    </w:abstractNum>';


        //We now try to open the zip file defined as base template
        try {
            $openBaseTemplate = $this->_baseTemplateZip->open($this->_baseTemplatePath);
            if ($openBaseTemplate !== true) {
                throw new Exception('Error while opening the Base Template: please, check the path');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        //We now extract the contents of the base template into a temp dir for further manipulation
        try {
            $this->_baseTemplateFilesPath = $this->_tempDir.'/'.uniqid(true);
            $extractBaseTemplate =$this->_baseTemplateZip->extractTo($this->_baseTemplateFilesPath);
            if ($extractBaseTemplate !== true) {
                throw new Exception('Error while extracting the Base Template: there may be problems writing in the default tmp folder');
            }
        }
        catch (Exception $e) {
          PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        //We should now check if there is any structured content as front page  to include it in the resulting document

        try{
            $baseTemplateDocumentT = $this->_baseTemplateZip->getFromName('word/document.xml');
            if ($baseTemplateDocumentT == '') {
                throw new Exception('Error while extracting the document.xml file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $baseDocument = new DOMDocument();
        $baseDocument->loadXML($baseTemplateDocumentT);
        $docXpath = new DOMXPath($baseDocument);
        $docXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $queryDoc = '//w:body/w:sdt';
        $docNodes = $docXpath->query($queryDoc);

        if ($docNodes->length > 0){
            if($docNodes->item(0)->nodeName == 'w:sdt'){
                $tempDoc = new DomDocument();
                $sdt =$tempDoc->importNode($docNodes->item(0), true);
                $newNode = $tempDoc->appendChild($sdt);
                $frontPage = $tempDoc->saveXML($newNode);
                $this->_wordDocumentC .= $frontPage;
            }
        }

        //Let us extract now the section information to include it at the end of the document.xml file

        $sectPr = $baseDocument->getElementsByTagName('sectPr')->item(0);
        $this->_sectPr = new DOMDocument();
        $sectNode = $this->_sectPr->importNode($sectPr, true);
        $this->_sectPr->appendChild($sectNode);

        //Let us extract the contents of the [Content_Types].xml file for further manipulation

        try {
            $baseTemplateContentTypeT = $this->_baseTemplateZip->getFromName('[Content_Types].xml');
            if ($baseTemplateContentTypeT  == '') {
                throw new Exception('Error while extracting the [Content_Types].xml file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $this->_contentTypeT = new DOMDocument();
        $this->_contentTypeT->loadXML($baseTemplateContentTypeT);

        //We are going to include the standard image defaults

        $this->generateDEFAULT('gif', 'image/gif');
        $this->generateDEFAULT('jpg', 'image/jpg');
        $this->generateDEFAULT('png', 'image/png');
        $this->generateDEFAULT('jpeg', 'image/jpeg');
        $this->generateDEFAULT('bmp', 'image/bmp');


        //Let us extract the document.xml.rels for further manipulation
        try {
            $baseTemplateDocumentRelsT = $this->_baseTemplateZip->getFromName('word/_rels/document.xml.rels');
            if ($baseTemplateDocumentRelsT == '') {
                throw new Exception('Error while extracting the document.xml.rels file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordRelsDocumentRelsT = new DOMDocument();
        $this->_wordRelsDocumentRelsT->loadXML($baseTemplateDocumentRelsT);
        $relationships = $this->_wordRelsDocumentRelsT->getElementsByTagName('Relationship');

        //Now we have to take care of the case that the template used is not one of the default preprocessed templates

        if ($this->_defaultTemplate) {
            self::$numUL = 1;
            self::$numOL = rand(9999, 999999999);

            //Let's get the original template numbering.xml file as a DOMdocument
            try {
                $this->_wordNumberingT = $this->_baseTemplateZip->getFromName('word/numbering.xml');
                if ($this->_wordNumberingT == '') {
                    throw new Exception('Error while extracting the numbering file from the base template');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        } else {
            //We should do now some cleaning of the files from the base template zip
            //Let us first look at the document.xml.rels file to analyze the contents
            //Let us analyze its structure
            //In order to do that we should parse word/_rels/document.xml.rels
            $counter = $relationships->length -1;

            for ($j=$counter; $j > -1; $j--) {
                $completeType = $relationships->item($j)->getAttribute('Type');
                $target = $relationships->item($j)->getAttribute('Target');
                $tempArray = explode('/', $completeType);
                $type = array_pop($tempArray);
                //This array holds the data that has to be changed in settings.xml
                $arrayCleaner = array();

                switch($type){
                    case 'header':
                        //TODO: this should be changed if we use default templates with headers
                        array_push($this->_relsHeader,$target);
                        break;
                    case 'footer':
                        //TODO: this should be changed if we use default templates with footers
                        array_push($this->_relsFooter,$target);
                        break;
                    case 'chart':
                        $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/charts');
                        $this->_wordRelsDocumentRelsT->documentElement->removeChild($relationships->item($j));
                        break;
                    case 'embeddings':
                        $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/embeddings');
                        $this->_wordRelsDocumentRelsT->documentElement->removeChild($relationships->item($j));
                        break;
                }

            }

           //Let us now manage the numbering.xml and style.xml files
           // We are going to use some default styles, for example, in the creation of lists, footnotes, titles, ...
           // So we should make sure that it is included in the styles.xml document
           $this->importStyles(PHPDOCX_BASE_TEMPLATE, 'merge', $this->_defaultPHPDOCXStyles);
           //Let us first check if the base template file has a numbering.xml file
           $numRef = rand(9999999, 99999999);
           self::$numUL = $numRef;
           self::$numOL = $numRef +1;

           if(file_exists($this->_baseTemplateFilesPath.'/word/numbering.xml')) {
                //Let's get the original template numbering.xml file as a DOMdocument
                try {
                    $this->_wordNumberingT = $this->_baseTemplateZip->getFromName('word/numbering.xml');
                    if ($this->_wordNumberingT == '') {
                        throw new Exception('Error while extracting the numbering file from the base template');
                    }
                } catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$unorderedListStyle, self::$numUL);
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, self::$numOL);
            }else{
                $this->_wordNumberingT = $this->generateBaseWordNumbering();
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$unorderedListStyle, self::$numUL);
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, self::$numOL);
                //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'numbering', 'numbering.xml'
                    );
                    $this->generateOVERRIDE('/word/numbering.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml');
            }

            //Let us now make sure that there are the corresponding xmls, with all their relationships for endnotes and footnotes
            if(!file_exists($this->_baseTemplateFilesPath.'/word/endnotes.xml') || !file_exists($this->_baseTemplateFilesPath.'/word/footnotes.xml')){
                $notesZip = new ZipArchive();
                try {
                    $openNotesZip = $notesZip->open(PHPDOCX_BASE_TEMPLATE);
                    if ($openNotesZip !== true){
                    throw new Exception('Error while opening the standard base template to extract the word/footnotes.xml  and word/endnotes.xml file');
                    }
                }
                catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }

                $arraySettings = array();
                if(!file_exists($this->_baseTemplateFilesPath.'/word/footnotes.xml')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/footnotes.xml');
                    //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'footnotes', 'footnotes.xml'
                    );
                   $this->generateOVERRIDE('/word/footnotes.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.footnotes+xml');
                   array_push($arraySettings, '<w:footnotePr><w:footnote w:id="-1" /><w:footnote w:id="0" /></w:footnotePr>');
                }
                if(!file_exists($this->_baseTemplateFilesPath.'/word/endnotes.xml')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/endnotes.xml');
                    //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'endnotes', 'endnotes.xml'
                    );
                   $this->generateOVERRIDE('/word/endnotes.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.endnotes+xml');
                   array_push($arraySettings,'<w:endnotePr><w:endnote w:id="-1" /><w:endnote w:id="0" /></w:endnotePr>');
                }

                //$this->includeSettings($arraySettings)
            }
        }
        $this->setLanguage($this->_phpdocxconfig['settings']['language']);

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
     * Magic method, returns current word XML
     *
     * @access public
     * @return string Return current word
     */
    public function __toString()
    {
        $this->generateTemplateWordDocument();
        PhpdocxLogger::logger('Get document template content.', 'debug');
        return $this->_wordDocumentT;
    }
    /**
     * Setter
     *
     * @access public
     */
    public function setExtension($extension)
    {
        $this->_extension = $extension;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getExtension()
    {
        return $this->_extension;
    }
    /**
     * Setter
     *
     * @access public
     */
    public function setTemporaryDirectory($tempDir)
    {
        $this->_tempDir = $tempDir;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getTemporaryDirectory()
    {
        return $this->_tempDir;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlContentTypes($xmlContentTypes)
    {
        $this->_contentTypeC = $xmlContentTypes;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlContentTypes()
    {
        return $this->_contentTypeC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlRelsRels($xmlRelsRels)
    {
        $this->_relsRelsC = $xmlRelsRels;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlRelsRels()
    {
        return $this->_relsRelsC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlDocPropsApp($xmlDocPropsApp)
    {
        $this->_docPropsAppC = $xmlDocPropsApp;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlDocPropsApp()
    {
        return $this->_docPropsAppC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlDocPropsCore($xmlDocPropsCore)
    {
        $this->_docPropsCoreC = $xmlDocPropsCore;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlDocPropsCore()
    {
        return $this->_docPropsCoreC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlDocPropsCustom($xmlDocPropsCustom)
    {
        $this->_docPropsCustomC = $xmlDocPropsCustom;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlDocPropsCustom()
    {
        return $this->_docPropsCustomC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordDocument($xmlWordDocument)
    {
        $this->_wordDocumentC = $xmlWordDocument;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordDocumentContent()
    {
        return $this->_wordDocumentC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordDocumentStyles($xmlWordDocumentStyles)
    {
        $this->_wordDocumentStyles = $xmlWordDocumentStyles;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordDocumentStyles()
    {
        return $this->_wordDocumentStyles;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordEndnotes($xmlWordEndnotes)
    {
        $this->_wordEndnotesC = $xmlWordEndnotes;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordEndnotes()
    {
        return $this->_wordEndnotesC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordFontTable($xmlWordFontTable)
    {
        $this->_wordFontTableC = $xmlWordFontTable;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordFontTable()
    {
        return $this->_wordFontTableC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordFooter1($xmlWordFooter)
    {
        $this->_wordFooterC = $xmlWordFooter;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordFooter1()
    {
        return $this->_wordFooterC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordHeader1($xmlWordHeader)
    {
        $this->_wordHeaderC = $xmlWordHeader;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordHeader1()
    {
        return $this->_wordHeaderC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordRelsDocumentRels($xmlWordRelsDocumentRels)
    {
        $this->_wordRelsDocumentRelsC = $xmlWordRelsDocumentRels;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordRelsDocumentRels()
    {
        return $this->_wordRelsDocumentRelsC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordSettings($xmlWordSettings)
    {
        $this->_wordSettingsC = $xmlWordSettings;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordSettings()
    {
        return $this->_wordSettingsC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordStyles($xmlWordStyles)
    {
        $this->_wordStylesC = $xmlWordStyles;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordStyles()
    {
        return $this->_wordStylesC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordThemeTheme1($xmlWordThemeTheme)
    {
        $this->_wordThemeThemeC = $xmlWordThemeTheme;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordThemeTheme1()
    {
        return $this->_wordThemeThemeC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordWebSettings($xmlWordWebSettings)
    {
        $this->_wordWebSettingsC = $xmlWordWebSettings;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function getXml_Word_WebSettings()
    {
        return $this->_wordWebSettingsC;
    }

    /**
     * Add a break
     *
     * @access public
     * @example ../examples/easy/PageBreak.php
     * @param string $options
     *  Values:
     * 'type' (line, page, column)
     */
    public function addBreak($options = array('type' => 'line'))
    {
        $break = CreatePage::getInstance();
        $break->generatePageBreak($options['type']);
        PhpdocxLogger::logger('Add break to word document.', 'info');
        $this->_wordDocumentC .= (string) $break;
    }

    /**
     * Add a chart
     *
     * @access public
     * @example ../examples/easy/Chart.php
     * @example ../examples/easy/Chart_bar.php
     * @param array $options
     *  Values: 'color' (1, 2, 3...) color scheme,
     *  'perspective' (20, 30...),
     *  'rotX' (20, 30...),
     *  'rotY' (20, 30...),
     *  'data' (array of values),
     *  'float' (left, right, center) floating image. It only applies if textWrap is not inline (default value).
     *  'font' (Arial, Times New Roman...),
     *  'groupBar' (clustered, stacked, percentStacked),
     *  'horizontalOffset' (int) given in emus (1cm = 360000 emus)
     *  'jc' (center, left, right),
     *  'showPercent' (0, 1),
     *  'sizeX' (10, 11, 12...),
     *  'sizeY' (10, 11, 12...),
     *  'textWrap' (0 (inline), 1 (square), 2 (front), 3 (back), 4 (up and bottom)),
     *  'verticalOffset' (int) given in emus (1cm = 360000 emus)
     *  'title',
     *  'type' (barChart, pieChart)
     *  'legendPos' (r, l, t, b, none),
     *  'legendOverlay' (0, 1),
     *  'border' (0, 1),
     *  'haxLabel' horizontal axis label,
     *  'vaxLabel' vertical axis label,
     *  'showtable' (0, 1) shows the table of values,
     *  'vaxLabelDisplay' (rotated, vertical, horizontal),
     *  'haxLabelDisplay' (rotated, vertical, horizontal),
     *  'hgrid' (0, 1, 2, 3),
     *  'vgrid' (0, 1, 2, 3),
     *  'style' this work only in radar charts.
     *  'gapWidth' distance between the pie and the second chart(ofpiechart)
     *  'secondPieSize' : size of the second chart(ofpiechart)
     *  'splitType' how decide to split the values :auto(Default Split), cust(Custom Split), percent(Split by Percentage), pos(Split by Position), val(Split by Value)
     *  'splitPos' split position , integer or float
     *  'custSplit' array of index to split
     *  'subtype' type of the second chart pie or bar
     *  'explosion' distance between the diferents values
     *  'holeSize' size of the hole in doughnut type
     *  'symbol'  array of symbols(scatter chart)
     *  'symbolSize' the size of the simbols
     *  'smooth' smooth the line (scatter chart)
     *  'wireframe' boolean(surface chart)to remove content color and only leave the border colors
     *  'showValue' (0,1) shows the values inside the chart
     *  'showCategory' (0,1) shows the category inside the chart
     */
    public function addChart($options = array())
    {
        PhpdocxLogger::logger('Create chart.', 'debug');
        try {
            if (isset($options['data']) && isset($options['type'])) {
                self::$intIdWord++;
                PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Chart.', 'debug');
                $type = $options['type'];
                if(strpos($type, 'Chart') === false)
                    $type .= 'Chart';

                $graphic = CreateChartFactory::createObject($type);

                if ($graphic->createGraphic(self::$intIdWord, $options) != false) {
                    PhpdocxLogger::logger('Add chart word/charts/chart' . self::$intIdWord .
                        '.xml to DOCX.', 'info');
                    $this->_zipDocx->addFromString(
                        'word/charts/chart' . self::$intIdWord . '.xml',
                        $graphic->getXmlChart()
                    );
                    $this->_wordRelsDocumentRelsC .=
                        $this->generateRELATIONSHIP(
                            'rId' . self::$intIdWord, 'chart',
                            'charts/chart' . self::$intIdWord . '.xml'
                        );
                    $this->generateDEFAULT('xlsx', 'application/octet-stream');
                    $this->generateOVERRIDE(
                        '/word/charts/chart' . self::$intIdWord . '.xml',
                        'application/vnd.openxmlformats-officedocument.' .
                        'drawingml.chart+xml'
                    );
                } else {
                    throw new Exception(
                        'There was an error related to the chart.'
                    );
                }
                $excel = $graphic->getXlsxType();

                $this->_tempFileXLSX[self::$intIdWord] =
                    tempnam($this->_tempDir, 'documentxlsx');
                if (
                    $excel->createXlsx(
                        $this->_tempFileXLSX[self::$intIdWord],
                        $options['data']
                    ) != false
                ) {
                    $this->_zipDocx->addFile(
                        $this->_tempFileXLSX[self::$intIdWord],
                        'word/embeddings/datos' . self::$intIdWord . '.xlsx'
                    );

                    $chartRels = CreateChartRels::getInstance();
                    $chartRels->createRelationship(self::$intIdWord);
                    $this->_zipDocx->addFromString(
                        'word/charts/_rels/chart' . self::$intIdWord .
                        '.xml.rels',
                        (string) $chartRels
                    );
                }
                $this->_wordDocumentC .= (string) $graphic;
            } else {
                throw new Exception(
                    'Images must have "data" and "type" values.'
                );
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add an image
     *
     * @access public
     * @example ../examples/easy/Image.php
     * @param array $data
     * Values:
     * 'border'(int) 1, 2, 3...
     * 'borderDiscontinuous' (0, 1)
     * 'float' (left, right, center) floating image. It only applies if textWrap is not inline (default value).
     * 'font' (string) Arial, Times New Roman...
     * 'horizontalOffset' (int) given in emus (1cm = 360000 emus). Only applies if there is the image is not floating
     * 'jc' (center, left, right, inside, outside)
     * 'name' (string) path to a local image
     * 'scaling' (int) 50, 100, ..
     * 'sizeX' (int) 10, 11, 12...
     * 'sizeY' (int) 10, 11, 12...
     * 'dpi' (int) dots per inch
     * 'spacingTop' (int) 10, 11...
     * 'spacingBottom' (int) 10, 11...
     * 'spacingLeft' (int) 10, 11...
     * 'spacingRight' (int) 10, 11...
     * 'textWrap' 0 (inline), 1 (square), 2 (front), 3 (back), 4 (up and bottom))
     * 'target' (string): document (default value), defaultHeader, firstHeader, evenHeader, defaultFooter, firstFooter, evenFooter
     * 'verticalOffset' (int) given in emus (1cm = 360000 emus)
     */
    public function addImage($data = '')
    {
        if(!isset($data['target'])){
           $data['target'] = 'document';
        }
        PhpdocxLogger::logger('Create image.', 'debug');
        try {
            if (isset($data['name']) && file_exists($data['name']) == 'true') {
                $attrImage = getimagesize($data['name']);
                try {
                    if ($attrImage['mime'] == 'image/jpg' ||
                        $attrImage['mime'] == 'image/jpeg' ||
                        $attrImage['mime'] == 'image/png' ||
                        $attrImage['mime'] == 'image/gif'
                    ) {
                        self::$intIdWord++;
                        PhpdocxLogger::logger('New ID rId' . self::$intIdWord . ' . Image.', 'debug');
                        $image = CreateImage::getInstance();
                        $data['rId'] = self::$intIdWord;
                        $image->createImage($data);
                        $dir = $this->parsePath($data['name']);
                        PhpdocxLogger::logger('Add image word/media/imgrId' .
                            self::$intIdWord . '.' . $dir['extension'] .
                            '.xml to DOCX.', 'info');
                        $this->_zipDocx->addFile(
                            $data['name'], 'word/media/imgrId' .
                            self::$intIdWord . '.' .
                            $dir['extension']
                        );
                        $this->generateDEFAULT(
                            $dir['extension'], $attrImage['mime']
                        );
                        if ((string) $image != ''){
                            //Here we consider the case where the image will be included in a header or footer
                            if($data['target'] == 'defaultHeader' ||
                               $data['target'] == 'firstHeader' ||
                               $data['target'] == 'evenHeader' ||
                               $data['target'] == 'defaultFooter' ||
                               $data['target'] == 'firstFooter' ||
                               $data['target'] == 'evenFooter'){
                                $this->_relsHeaderFooterImage[$data['target']][] =
                                array('rId' => 'rId' . self::$intIdWord, 'extension' => $dir['extension']);
                            }else{
                                $this->_wordRelsDocumentRelsC .=
                                    $this->generateRELATIONSHIP(
                                        'rId' . self::$intIdWord, 'image',
                                        'media/imgrId' . self::$intIdWord . '.'
                                        . $dir['extension']
                                    );
                            }
                        }
                        $this->_wordDocumentC .= (string) $image;
                    } else {
                        throw new Exception('Image format is not supported.');
                    }
                }
                catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }
            } else {
                throw new Exception('Image does not exist.');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add a link
     *
     * @access public
     * @example ../examples/easy/Link.php
     * @param array $options
     * @see addText
     * additional parameter:
     * 'url' (string) URL or #bookmarkName
     *
     */
    public function addLink($text, $options = array('url' => '',
                                                    'font' => '',
                                                    'sz' => '',
                                                    'color' => '0000ff',
                                                    'u' => 'single',
                                                    ))
    {
        if(substr($options['url'], 0, 1) == '#'){
            $url = 'HYPERLINK \l "' . substr($options['url'], 1) . '"';
        }else{
            $url = 'HYPERLINK "' . $options['url'] . '"';
        }
        if ($text == '') {
            PhpdocxLogger::logger('The linked text is missing', 'fatal');
        } else if($options['url'] == '') {
            PhpdocxLogger::logger('The URL is missing', 'fatal');
        }
        if (isset($options['color'])) {
            $color = $options['color'];
        } else {
            $color = '0000ff';
        }
        if (isset($options['u'])) {
            $u = $options['u'];
        } else {
            $u = 'single';
        }
        $textOptions = $options;
        $textLink = CreateText::getInstance();
        $textLink->createText($text, $textOptions);
        $link = (string) $textLink;
        $link = preg_replace('/__[A-Z]+__/', '', $link);
        $startNodes ='<w:r><w:fldChar w:fldCharType="begin" /></w:r><w:r>
        <w:instrText xml:space="preserve">'.$url.'</w:instrText>
        </w:r><w:r><w:fldChar w:fldCharType="separate" /></w:r>';
        if(strstr($link, '</w:pPr>')){
            $link = preg_replace('/<\/w:pPr>/', '</w:pPr>'.$startNodes, $link);
        }else{
            $link = preg_replace('/<w:p>/', '<w:p>'.$startNodes, $link);
        }
        $endNode = '<w:r><w:fldChar w:fldCharType="end" /></w:r>';
        $link = preg_replace('/<\/w:p>/', $endNode . '</w:p>', $link);
        PhpdocxLogger::logger('Add link to word document.', 'info');
        $this->_wordDocumentC .= (string) $link;
    }

    /**
     * Add a list
     *
     * @access public
     * @example ../examples/easy/List.php
     * @param array $data Values of the list
     * @param array $options
     *  Values:
     * 'font' (string), Arial, Times New Roman, ...
     * 'val' (int), 0 (clear), 1 (inordinate), 2(numerical)
     * 'bullets' (array) 1 (), 2 (o), 3 ()
     */
    public function addList($data, $options = array())
    {
        $list = CreateList::getInstance();

        if ($options['val'] == 2){
            self::$numOL++;
            $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, self::$numOL);
        }
        $list->createList($data, $options);
        PhpdocxLogger::logger('Add list to word document.', 'info');
        $this->_wordDocumentC .= (string) $list;

        if (!empty($options['bullets'])
            && is_array($options['bullets'])
            && $options['val'] == 1
        ) {
            for ($i = 0; $i <= CreateList::MAXDEPTH; $i++) {
                $bullets = $options['bullets'];
                        if (isset($bullets[$i])) {
                            $styleId = $bullets[$i];
                        } else {
                            $styleId = $i;
                        }
                $list->createListStyles($i, $styleId);
                PhpdocxLogger::logger('Add list styles to word document.', 'info');
                $this->_wordDocumentStyles .= (string) $list;
            }
        }
    }

    /**
     * Add a raw WordML
     *
     * @access public
     * @param string $wml WordML to add
     * @deprecated See addWordML
     */
    public function addRawWordML($wml)
    {
        PhpdocxLogger::logger('Add raw WordML.', 'info');
        $this->_wordDocumentC .= $wml;
    }

    /**
     * Add a table.
     *
     * @access public
     * @example ../examples/easy/Table.php
     * @param array $tableData an array of arrays with the table data organized by rows
     * Each cell content may be a string or array.
     * If the cell contents are in the form of an array its keys and posible values are:
     *      'value' (string)
     *      'rowspan' (int)
     *      'colspan' (int)
     *      'width' (int) in twentieths of a point
     *      'border' (none, single, double, dashed, threeDEngrave, threeDEmboss, outset, inset)
     *      'border_color' (ffffff, ff0000)
     *      'border_spacing' (0, 1, 2...)
     *      'border_sz' (10, 11...) in eights of a point
     *      'border_<side>' (none, single, double, dashed, threeDEngrave, threeDEmboss, outset, inset) where the side may be: top, left, right or bottom
     *      'border_<side>_color' (ffffff, ff0000)
     *      'border_<side>_spacing' (0, 1, 2...)
     *      'border_<side>_sz' (10, 11...)
     *      'background_color' (ffffff, ff0000)
     *      'noWrap' (boolean)
     *      'cellMargin' (mixed) an integer value or an array:
     *          'top' (int) in twentieths of a point
     *          'right' (int) in twentieths of a point
     *          'bottom' (int) in twentieths of a point
     *          'left' (int) in twentieths of a point
     *      'textDirection' (string) available values are: tbRl and btLr
     *      'fitText' (boolean) if true fits the text to the size of the cell
     *      'vAlign' (string) vertical align of text: top, center, both or bottom
     *
     * @param array $tableProperties Parameters to use
     *  Values:
     *  'border' (none, single, double, dashed, threeDEngrave, threeDEmboss, outset, inset)
     *  'border_color' (ffffff, ff0000)
     *  'border_spacing' (0, 1, 2...)
     *  'border_sz' (10, 11...) in eights of a point
     *  'border_settings' (all, outside, inside) if all (default value) the border styles apply to all table borders.
     *  If the value is set to outside or inside the border styles will only apply to the outside or inside boreders respectively.
     *  'cantSplitRows' (boolean) set global row split properties (can be overriden by rowProperties)
     *  'cellMargin' (array) the keys are top, right, bottom and left and the values is given in twips (twentieths of a point)
     *  'cellSpacing' (int) given in twips (twentieths of a point)
     *  'float' (array) with the following keys and values:
     *      'textMargin_top' (int) in twentieths of a point
     *      'textMargin_right' (int) in twentieths of a point
     *      'textMargin_bottom' (int) in twentieths of a point
     *      'textMargin_left' (int) in twentieths of a point
     *      'align' (string) posible values are: left, center, right, outside, inside
     *  'font' (Arial, Times New Roman...)
     *  'indent' (int) given in twips (twentieths of a point)
     *  'jc' (center, left, right)
     *  'decimalTab'
     *  'size_col': column width fix (int)
     *              column width variable (array)
     *  'tableWidth' (array) its posible keys and values are:
     *      'type' (pct, dxa) pct if the value refers to percentage and dxa if the value is given in twentieths of a point (twips)
     *      'value' (int)
     *  'TBLSTYLEval' (string) Word table style
     *
     * @param array $rowProperties (array) a cero based array. Each entry is an array with keys and values:
     *      'cantSplit' (boolean)
     *      'minHeight' (int) in twentieths of a point
     *      'height' (int) in twentieths of a point
     *      'tblHeader' (boolean) if true this row repeats at the beguinning of each new page
     */
    public function addTable($tableData, $tableProperties= array(), $rowProperties = array())
    {
        $table = CreateTable::getInstance();
        $table->createTable($tableData, $tableProperties, $rowProperties);
        PhpdocxLogger::logger('Add table to Word document.', 'info');
        $this->_wordDocumentC .= (string) $table;
    }

    /**
     * Add a text
     *
     * @access public
     * @example ../examples/easy/Text.php
     * @example ../examples/easy/Text_cursive.php
     * @param mixed $textParams if a string just the text to be included, if an
     * array is or an array of arrays with each element containing
     * the text to be inserted and their formatting properties
     * Array values:
     * 'text' (string) the run of text to be inserted
     * 'b' (on, off)
     * 'caps' (on, off) display text in capital letters
     * 'color' (ffffff, ff0000...)
     * 'columnBreak' (before, after, both) inserts a column break before, after or both, a run of text
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'lineBreak' (before, after, both) inserts a line break before, after or both, a run of text
     * 'sz' (1, 2, 3...)
     * 'tab' (boolean) inserts a tab. Default value is false
     * 'spaces': number of spaces at the beguinning of the run of text
     * 'u' (none, dash, dotted, double, single, wave, words)
     * @param array $paragraphParams Style options to apply to the whole paragraph
     *  Values:
     * 'pStyle' (string) Word style to be used. Run parseStyles() to check all available paragraph styles
     * 'b' (on, off)
     * 'caps' (on, off) display text in capital letters
     * 'color' (ffffff, ff0000...)
     * 'contextualSpacing' (on, off) ignore spacing above and below when using identical styles
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'jc' (both, center, distribute, left, right)
     * 'keepLines' (on, off) keep all paragraph lines on the same page
     * 'keepNext' (on, off) keep in the same page the current paragraph with next paragraph
     * 'lineSpacing' 120, 240 (standard), 360, 480, ...
     * 'pageBreakBefore' (on, off)
     * 'spacingBottom' (int) bottom margin in twentieths of a point
     * 'spacingTop' (int) top margin in twentieths of a point
     * 'sz' (8, 9, 10, ...) size in points
     * 'tabPositions' (array) each entry is an associative array with the following keys and values
     *      'type' (string) can be clear, left (default), center, right, decimal, bar and num
     *      'leader' (string) can be none (default), dot, hyphen, underscore, heavy and middleDot
     *      'position' (int) given in twentieths of a point
     * if there is a tab and the tabPositions array is not defined the standard tab position (default of 708) will be used
     * 'textDirection' (lrTb, tbRl, btLr, lrTbV, tbRlV, tbLrV) text flow direction
     * 'u' (none, dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     */
    public function addText($textParams, $paragraphParams = array())
    {
        $text = CreateText::getInstance();
        $text->createText($textParams, $paragraphParams);
        PhpdocxLogger::logger('Add text to word document.', 'info');
        $this->_wordDocumentC .= (string) $text;
    }

    /**
     * Generate a new DOCX file
     *
     * @access public
     * @example ../examples/easy/Text.php
     * @param string $args[0] File name
     * @param string $args[1] Page style
     *  Values: 'bottom' (4000, 4001...), 'columns' (1, 2, 3), 'left' (4000, 4001...),
     *  'orient' (landscape), 'right' (4000, 4001), 'titlePage' (1),
     *  'top' (4000, 4001)
     */
    public function createDocx()
    {
        $args = func_get_args();
        if (!empty($args[0])) {
            $fileName = $args[0];
        } else {
            $fileName = 'document';
        }
        PhpdocxLogger::logger('Set DOCX name to: ' . $fileName . '.', 'info');
        PhpdocxLogger::logger('DOCX is a new file, not a template.', 'debug');
        //We copy the rels content into the respective file
        $relsHandler = fopen($this->_baseTemplateFilesPath.'/word/_rels/document.xml.rels', "w+");
        fwrite($relsHandler, $this->_wordRelsDocumentRelsT->saveXML());
        fclose($relsHandler);
        //We also copy the contents of the [Content_types].xml file
        $contentTypesHandler = fopen($this->_baseTemplateFilesPath.'/[Content_Types].xml', "w+");
        fwrite($contentTypesHandler, $this->_contentTypeT->saveXML());
        fclose($contentTypesHandler);
        $arrArgsPage = array();
        $this->generateTemplateWordDocument($arrArgsPage);
        if ($this->_debug->getActive() == 1) {
            PhpdocxLogger::logger('Debug is active, add messages to objDebug.', 'debug');
            libxml_use_internal_errors(true);
            simplexml_load_string(
                $this->_wordDocumentT, 'SimpleXMLElement', LIBXML_NOWARNING
            );
            $xmlErrors = libxml_get_errors();
            if (is_array($xmlErrors)) {
                $this->_debug->addMessage($xmlErrors);
                libxml_clear_errors();
            }
        }
        PhpdocxLogger::logger('Add word/document.xml content to DOCX file.', 'info');
        $documentHandler = fopen($this->_baseTemplateFilesPath.'/word/document.xml', "w+");
        if (self::$_encodeUTF) {
            $contentDocumentXML = utf8_encode($this->_wordDocumentT);
            //TODO: sot out encoding problems
            fwrite($documentHandler, utf8_encode($this->_wordDocumentT));
        } else {
            if ($this->_phpdocxconfig['settings']['encode_to_UTF8'] == 'true' && !PhpdocxUtilities::isUtf8($this->_wordDocumentT)) {
                $contentDocumentXML = utf8_encode($this->_wordDocumentT);
            } else {
                $contentDocumentXML = $this->_wordDocumentT;
            }
            fwrite($documentHandler, $this->_wordDocumentT);
        }
        fclose($documentHandler);
        if($this->_wordFootnotesC != ''){
            PhpdocxLogger::logger('Add word/footnote.xml content to DOCX file.', 'info');
            $footnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/footnote.xml', "w+");
                if (self::$_encodeUTF) {
                //TODO: sot out encoding problems
                    fwrite($footnoteHandler, utf8_encode($this->_wordFootnotesT));
                } else {
                    if ($this->_phpdocxconfig['settings']['encode_to_UTF8'] == 'true') {
                        if (!PhpdocxUtilities::isUtf8($this->_wordFootnotesT)) {
                            $this->_wordFootnotesT = utf8_encode($this->_wordFootnotesT);
                        }
                    }
                    fwrite($footnoteHandler, $this->_wordFootnotesT);
                }
            fclose($documentHandler);
            }
        $numberingHandler = fopen($this->_baseTemplateFilesPath.'/word/numbering.xml', "w+");
        fwrite($numberingHandler, $this->_wordNumberingT);
        fclose($numberingHandler);
        PhpdocxLogger::logger('Close ZIP file', 'info');
        $this->recursiveInsert($this->_zipDocx, $this->_baseTemplateFilesPath, $this->_baseTemplateFilesPath);
        //Lets now insert the photos inserted by the embedHTML method
        if (is_dir($this->_baseTemplateFilesPath.'/word/mediaTemplate')){
            $contentsDir = scandir($this->_baseTemplateFilesPath.'/word/mediaTemplate');
            $predefinedExtensions = explode(',', PHPDOCX_ALLOWED_IMAGE_EXT);
            foreach($contentsDir as $element){
                $arrayExtension = explode('.', $element);
                $extension = strtolower(array_pop($arrayExtension));
                if (in_array($extension, $predefinedExtensions)){
                    $this->_zipDocx->addFile($this->_baseTemplateFilesPath.'/word/mediaTemplate/'.$element, 'word/media/'.$element);
                }
                //Now we remove the image from the mediaTemplate folder
                $this->_zipDocx->deleteName('word/mediaTemplate/'.$element);
            }
            //And now we delete the mediaTemplate folder
            $deleteMediaTemplate = $this->_zipDocx->deleteName('word/mediaTemplate/');
        }
        //Check if there are openbookmars and if so throw an error
        if (count($this->_bookmarksIds) > 0) {
            PhpdocxLogger::logger('There are unclosed bookmarks. Please, check that all open bookmarks tags are properly closed.', 'fatal');
        }
        $this->_zipDocx->close();
        $arrpathFile = pathinfo($fileName);
        PhpdocxLogger::logger('Copy DOCX file using a new name.', 'info');
        copy(
            $this->_tempFile,
            $fileName . '.' . $this->_extension
        );
        if ($this->_debug->getActive() == 1) {
            PhpdocxLogger::logger('Debug is active, show messages.', 'debug');
            echo $this->_debug;
        }
        // delete temp file
        if (is_file($this->_tempFile) && is_writable($this->_tempFile)) {
            unlink($this->_tempFile);
        }
    }

    /**
     *
     * Transform a word document to a text file
     *
     * @example ../examples/easy/Docx2Text.php
     * @param string $path. Path to the docx from which we wish to import the content
     * @param string $path. Path to the text file output
     * @param array styles.
     * keys: table => true/false,list => true/false, paragraph => true/false, footnote => true/false, endnote => true/false, chart => (0=false,1=array,2=table)
     */
    public static function docx2txt($from, $to, $options = array()) {
        $text = new Docx2Text($options);
        $text->setDocx($from);
        $text->extract($to);
    }

    /**
     * Imports an existing style sheet from an existing docx document.
     *
     * @access private
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     * @param string $type. You may choose 'replace' (overwrites the current styles) or 'merge' (adds the selected styles)
     * @param array $myStyles. A list of specific styles to be merged. If it is empty or the choosen type is 'replace' it will be ignored.
     */
    private function importStyles($path, $type= 'replace', $myStyles= array(), $styleIdentifier = 'styleName')
    {
        $zipStyles = new ZipArchive();
       try {
        $openStyle = $zipStyles->open($path);
        if ($openStyle !== true) {
           throw new Exception('Error while opening the Style Template: please, check the path');
         }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        if ($type == 'replace') {
            //Now we overwrite the original styles file
            try {
                $extractingStyleFile = $zipStyles->extractTo($this->_baseTemplateFilesPath.'/','word/styles.xml');
                if (!$extractingStyleFile) {
                    throw new Exception('Error while trying to overwrite the styles.xml of the base template');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
            //In order not to loose certain styles needed for certain PHPDOCX methods we should merge them
            $this->importStyles(PHPDOCX_BASE_TEMPLATE, 'merge', $this->_defaultPHPDOCXStyles);
        } else {
            //We will first extract the new styles from the external docx
            try {
                $newStyles = $zipStyles->getFromName('word/styles.xml');
                if ($newStyles == '') {
                    throw new Exception('Error while extracting the styles from the external docx');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        //let's parse the different styles via XPath
        $newStylesDoc = new DOMDocument();
        $newStylesDoc->loadXML($newStyles);
        $stylesXpath = new DOMXPath($newStylesDoc);
        $stylesXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $queryStyle = '//w:style';
        $styleNodes = $stylesXpath->query($queryStyle);

        //Let's get the original styles as a DOMdocument
        try{
            $styleHandler = fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'r');
            $styleXML = fread($styleHandler, filesize($this->_baseTemplateFilesPath.'/word/styles.xml'));
            fclose($styleHandler);
            $this->_wordStylesT = $styleXML;
            if ($styleXML == '') {
                throw new Exception('Error while extracting the style file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $stylesDocument = new DomDocument();
        $stylesDocument->loadXML($this->_wordStylesT);
        $baseNode = $stylesDocument->documentElement;
        $stylesDocumentXPath = new DOMXPath($stylesDocument);
        $stylesDocumentXPath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $query = '//w:style';
        $originalNodes = $stylesDocumentXPath->query($query);

        //Now we start to insert the new styles at the end of the styles.xml
        foreach($styleNodes as $node){
           // in order to avoid duplicated Ids we first remove from the
           // original styles.xml any duplicity with the new ones
           // TODO: check performance
            foreach($originalNodes as $oldNode){
                if($styleIdentifier == 'styleID'){
                    if($oldNode->getAttribute('w:styleId') == $node->getAttribute('w:styleId')
                       &&  in_array($oldNode->getAttribute('w:styleId'), $myStyles)){
                        $oldNode->parentNode->removeChild($oldNode);
                    }
                }else{
                    $oldName = $oldNode->getElementsByTagName('w:name');
                    if($oldNode->getAttribute('w:styleId') == $node->getAttribute('w:styleId')
                       &&  in_array($oldName, $myStyles)){
                        $oldNode->parentNode->removeChild($oldNode);
                    }
                }
            }
           if(count($myStyles)>0){
               //Lets insert the selected styles
               if($styleIdentifier == 'styleID'){
                   if(in_array($node->getAttribute('w:styleId'), $myStyles)){
                    $insertNode = $stylesDocument->importNode($node, true);
                    $baseNode->appendChild($insertNode);
                   }
               }else{
               $nodeChilds = $node->childNodes;
               foreach($nodeChilds as $child){
                   if ($child->nodeName == 'w:name'){
                       $styleName = $child->getAttribute('w:val');
                       if(in_array($styleName, $myStyles)){
                        $insertNode = $stylesDocument->importNode($node, true);
                        $baseNode->appendChild($insertNode);
                       }
                    }
                  }
               }
           }else{
           $insertNode = $stylesDocument->importNode($node, true);
           $baseNode->appendChild($insertNode);
           }
        }
        $this->_wordStylesT = $stylesDocument->saveXML();
        try {
            $stylesFile=fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'w');
            if ($stylesFile == false) {
                throw new Exception('Error while opening the base template styles.xml file');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeStyles = fwrite($stylesFile,$this->_wordStylesT);
            if ($writeStyles == 0) {
                throw new Exception('There were no new styles written');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

      }
      PhpdocxLogger::logger('Importing styles from an external docx.', 'info');
    }

    /**
     * Imports an existing theme from an existing docx document.
     *
     * @access private
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    private function importThemeXML($path){
        try {
            $zipTheme = new ZipArchive();
            $extractingThemeFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/theme/theme1.xml');
            if (!$extractingThemeFile) {
                throw new Exception('Error while trying to overwrite the theme1.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Imports an existing webSettings.xml file from an existing docx document.
     *
     * @access private
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    private function importWebSettingsXML($path){
        try {
            $zipWebSettings = new ZipArchive();
            $extractingWebSettingsFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/webSettings.xml');
            if (!$extractingWebSettingsFile) {
                throw new Exception('Error while trying to overwrite the webSettings.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Imports an existing settings.xml file from an existing docx document.
     *
     * @access private
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    private function importSettingsXML($path){
        try {
            $zipSettings = new ZipArchive();
            $extractingSettingsFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/settings.xml');
            if (!$extractingSettingsFile) {
                throw new Exception('Error while trying to overwrite the settings.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Imports an existing fontTable.xml file from an existing docx document.
     *
     * @access private
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    private function importFontTableXML($path){
        try {
            $zipFontTable = new ZipArchive();
            $extractingFontTableFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/fontTable.xml');
            if (!$extractingFontTableFile) {
                throw new Exception('Error while trying to overwrite the fontTable.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Transform to UTF-8 charset
     *
     * @access public
     */
    public function setEncodeUTF8()
    {
        self::$_encodeUTF = 1;
    }

    /**
     * Change default language.
     * @example ../examples/easy/Language.php
     * @param $lang Locale: en-US, es-ES...
     * @access public
     */
    public function setLanguage($lang = null)
    {
        if (!$lang) {
            $lang = 'en-US';
        }
        //Let's get the original styles as a DOMdocument
        try{
            $styleHandler = fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'r');
            $styleXML = fread($styleHandler, 10000000);
            fclose($styleHandler);
            $this->_wordStylesT = $styleXML;
            if ($styleXML == '') {
                throw new Exception('Error while extracting the style file from the base template to stablish default language');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $stylesDocument = new DomDocument();
        $stylesDocument->loadXML($this->_wordStylesT);
        $langNode = $stylesDocument->getElementsByTagName('lang');
        $langNode->item(0)->setAttribute('w:val', $lang);
        $langNode->item(0)->setAttribute('w:eastAsia', $lang);

        $this->_wordStylesT = $stylesDocument->saveXML();
        try {
            $stylesFile=fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'w');
            if ($stylesFile == false) {
                throw new Exception('Error while opening the base template styles.xml file');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeStyles = fwrite($stylesFile,$this->_wordStylesT );
            if ($writeStyles == 0) {
                throw new Exception('There was an error while trying to set the default language');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        PhpdocxLogger::logger('Set language.', 'info');
    }

    /**
     * Add style
     *
     * @param string lang Language
     * @access private
     */
    private function addStyle($lang = 'en-US')
    {
        $style = CreateStyle::getInstance();
        $style->createStyle($lang);
        PhpdocxLogger::logger('Add styles to styles document.', 'info');
        $this->_wordStylesC .= (string) $style;
    }

    /**
     * Imports styles into the template stylesheet.
     *
     * @access private
     * @param string $templateStyles
     * @param DOMDocument $importedStylesheet
     */
    private function addStylesTemplate($templateStyles, $importedStylesheet)
    {

        $templateStylesheet = new DomDocument();
        $templateStylesheet->loadXML($templateStyles);
        //let's parse the different styles via XPath

        $stylesXpath = new DOMXPath($importedStylesheet);
        $stylesXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $queryStyle = '//w:style';
        $styleNodes = $stylesXpath->query($queryStyle);

        //Let's get the original styles as a DOMNode
        $stylesDocument = new DomDocument();
        $stylesDocument->loadXML($templateStyles);
        $baseNode = $stylesDocument->documentElement;

        //Now we start to insert the new styles at the end of the styles.xml
        foreach ($styleNodes as $node) {
           // in order to avoid duplicated Ids we first remove from the
           // original styles any duplicity with the new ones
            $originalNodes = $stylesDocument->childNodes;
            foreach($originalNodes as $oldNode) {
                if ($oldNode->getAttribute('w:styleId') == $node->getAttribute('w:styleId')) {
                    $oldNode->parent->removeChild($oldNode);
                }
            }
            $insertNode = $stylesDocument->importNode($node, true);
            $baseNode->appendChild($insertNode);
        }
        PhpdocxLogger::logger('Importing styles into the template stylesheet.', 'info');

        return $stylesDocument->saveXML();
    }

    /**
     * Generate content type
     *
     * @access private
     */
    private function generateContentType()
    {
        $this->generateDEFAULT(
            'rels', 'application/vnd.openxmlformats-package.relationships+xml'
        );
        $this->generateDEFAULT('xml', 'application/xml');
        $this->generateDEFAULT('htm', 'application/xhtml+xml');
        $this->generateDEFAULT('rtf', 'application/rtf');
        $this->generateDEFAULT('zip', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml');
        $this->generateDEFAULT('mht', 'message/rfc822');
        $this->generateDEFAULT('wml', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml');
        $this->generateOVERRIDE(
            '/word/numbering.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml.' .
            'numbering+xml'
        );
        $this->generateOVERRIDE(
            '/word/styles.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.styles+xml'
        );
        $this->generateOVERRIDE(
            '/docProps/app.xml',
            'application/vnd.openxmlformats-officedocument.extended-' .
            'properties+xml'
        );
        $this->generateOVERRIDE(
            '/docProps/custom.xml',
            'application/vnd.openxmlformats-officedocument.' .
            'custom-properties+xml'
        );
        $this->generateOVERRIDE(
            '/word/settings.xml', 'application/' .
            'vnd.openxmlformats-officedocument.wordprocessingml.settings+xml'
        );
        $this->generateOVERRIDE(
            '/word/theme/theme1.xml',
            'application/vnd.openxmlformats-officedocument.theme+xml'
        );
        $this->generateOVERRIDE(
            '/word/fontTable.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml.' .
            'fontTable+xml'
        );
        $this->generateOVERRIDE(
            '/word/webSettings.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.webSettings+xml'
        );
        if ($this->_wordFooterC != '' || $this->_wordHeaderC != '') {
            $this->generateOVERRIDE(
                '/word/header.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.header+xml'
            );
            $this->generateOVERRIDE(
                '/word/footer.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.footer+xml'
            );
            $this->generateOVERRIDE(
                '/word/footnotes.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.footnotes+xml'
            );
            $this->generateOVERRIDE(
                '/word/endnotes.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.endnotes+xml'
            );
        }
        $this->generateOVERRIDE(
            '/docProps/core.xml',
            'application/vnd.openxmlformats-package.core-properties+xml'
        );
    }

    /**
     * Generate DEFAULT
     *
     * @access private
     */
    private function generateDEFAULT($extension, $contentType)
    {
        $strContent = $this->_contentTypeT->saveXML();
        if (
            strpos($strContent, 'Extension="' . $extension)
            === false
        ) {
            $strContentTypes = '<Default Extension="'.$extension .'" ContentType="'. $contentType .'"> </Default>';
            $tempNode = $this->_contentTypeT->createDocumentFragment();
            $tempNode->appendXML($strContentTypes);
            $this->_contentTypeT->documentElement->appendChild($tempNode);
        }
    }

    /**
     *
     *
     * @access private
     */
    private function generateDefaultFonts()
    {
        $font = array(
            'name' => 'Calibri', 'pitch' => 'variable', 'usb0' => 'A00002EF',
            'usb1' => '4000207B', 'usb2' => '00000000', 'usb3' => '00000000',
            'csb0' => '0000009F', 'csb1' => '00000000', 'family' => 'swiss',
            'charset' => '00', 'panose1' => '020F0502020204030204'
        );
        $this->addFont($font);
        $font = array(
            'name' => 'Times New Roman', 'pitch' => 'variable',
            'usb0' => 'E0002AEF', 'usb1' => 'C0007841', 'usb2' => '00000009',
            'usb3' => '00000000', 'csb0' => '000001FF', 'csb1' => '00000000',
            'family' => 'roman', 'charset' => '00',
            'panose1' => '02020603050405020304'
        );
        $this->addFont($font);
        $font = array(
            'name' => 'Cambria', 'pitch' => 'variable', 'usb0' => 'A00002EF',
            'usb1' => '4000004B', 'usb2' => '00000000', 'usb3' => '00000000',
            'csb0' => '0000009F', 'csb1' => '00000000', 'family' => 'roman',
            'charset' => '00', 'panose1' => '02040503050406030204'
        );
        $this->addFont($font);
    }

    /**
     * Generate DefaultWordRels
     *
     * @access private
     */
    private function generateDefaultWordRels()
    {
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . numbering.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'numbering', 'numbering.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . theme/theme1.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'theme', 'theme/theme1.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . numbering.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'webSettings', 'webSettings.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . webSettings.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'fontTable', 'fontTable.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . fontTable.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'settings', 'settings.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . settings.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'styles', 'styles.xml'
        );
    }


    /**
     * Generate OVERRIDE
     *
     * @access private
     * @param string $partName
     * @param string $contentType
     */
    private function generateOVERRIDE($partName, $contentType)
    {
        $strContent = $this->_contentTypeT->saveXML();
        if (
            strpos($strContent, 'PartName="' . $partName . '"')
            === false
        ) {
            $strContentTypes = '<Override PartName="'.$partName.'" ContentType="'.$contentType.'" />';
            $tempNode = $this->_contentTypeT->createDocumentFragment();
            $tempNode->appendXML($strContentTypes);
            $this->_contentTypeT->documentElement->appendChild($tempNode);
        }
    }

    /**
     * Generate RELATIONSHIP
     *
     * @access private
     */
    private function generateRELATIONSHIP()
    {
        $arrArgs = func_get_args();
        if ($arrArgs[1] == 'vbaProject') {
            $type =
            'http://schemas.microsoft.com/office/2006/relationships/vbaProject';
        } else {
            $type =
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships/' . $arrArgs[1];
        }

        if (!isset($arrArgs[3])) {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '"></Relationship>';

        } else {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '" ' . $arrArgs[3] .
               '></Relationship>';
        }
      $relsNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
       $relsNode->appendXML($nodeWML);
       $this->_wordRelsDocumentRelsT->documentElement->appendChild($relsNode);


    }

        /**
     * Gnerate RELATIONSHIP
     *
     * @access private
     */
    private function generateRELATIONSHIPTemplate()
    {
        $arrArgs = func_get_args();
        if ($arrArgs[1] == 'vbaProject') {
            $type =
            'http://schemas.microsoft.com/office/2006/relationships/vbaProject';
        } else {
            $type =
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships/' . $arrArgs[1];
        }

        if (!isset($arrArgs[3])) {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '"></Relationship>';

        } else {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '" ' . $arrArgs[3] .
               '></Relationship>';
        }

       return $nodeWML;
    }

    /**
     * Generate SECTPR
     *
     * @access private
     * @param array $args Section style
     */
    private function generateSECTPR($args = '')
    {
        $page = CreatePage::getInstance();
        $page->createSECTPR($args);
        $this->_wordDocumentC .= (string) $page;
    }

    /**
     * Generates an element in settings.xml
     *
     * @access private
     */
    private function generateSetting($tag)
    {
        if((!in_array($tag, self::$settings))){
           self::$log->fatal('Incorrect setting tag');
        }
        $settingIndex = array_search($tag, self::$settings);
        try{
            $settings = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "r");
            $baseTemplateSettingsT = fread($settings, 1000000);
            fclose($settings);
            if ($baseTemplateSettingsT == '') {
                throw new Exception('Error while extracting settings.xml file from the base template to insert the selected element');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordSettingsT = new DOMDocument();
        $this->_wordSettingsT->loadXML($baseTemplateSettingsT);
        $selectedElements = $this->_wordSettingsT->documentElement->getElementsByTagName($tag);
        if($selectedElements->length == 0){
            $settingsElement = $this->_wordSettingsT->createDocumentFragment();
            $settingsElement->appendXML('<' . $tag . ' xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />');
            $childNodes = $this->_wordSettingsT->documentElement->childNodes;
            $index = false;
            foreach($childNodes as $node){
                $name = $node->nodeName;
                $index = array_search($node->nodeName, self::$settings);
                if($index > $settingIndex){
                    $node->parentNode->insertBefore($settingsElement, $node);
                    break;
                }
            }
            //in case no node was found (pretty unlikely)we should append the node
            if (!$index) {
                $this->_wordSettingsT->documentElement->appendChild($settingsElement);
            }
            $newSettings = $this->_wordSettingsT->saveXML();
            $settingsHandle = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
            $contents = fwrite($settingsHandle, $newSettings);
            fclose($settingsHandle);
        }

    }

    /**
     * Generate ContentType XML template
     *
     * @access private
     */
    private function generateTemplateContentType()
    {
        $this->_wordContentTypeT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>' .
            '<Types xmlns="http://schemas.openxmlformats.org/package/2006/' .
            'content-types">' . $this->_contentTypeC . '</Types>';
    }

    /**
     * Generate DocPropsApp XML template
     *
     * @access private
     */
    private function generateTemplateDocPropsApp()
    {
        $this->_docPropsAppT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Properties xmlns="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/extended-properties" xmlns:vt="' .
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'docPropsVTypes"><Template>Normal.dotm</Template><TotalTime>' .
            '0</TotalTime><Pages>1</Pages><Words>1</Words><Characters>1'
            . '</Characters><Application>Microsoft Office Word</Application>' .
            '<DocSecurity>4</DocSecurity><Lines>1</Lines><Paragraphs>1' .
            '</Paragraphs><ScaleCrop>false</ScaleCrop>';
        if ($this->_docPropsAppC) {
            $this->_docPropsAppT .= $this->_docPropsAppC;
        } else {
            $this->_docPropsAppT .= '<Company>Company</Company>';
        }
        $this->_docPropsAppT .= '<LinksUpToDate>false</LinksUpToDate>' .
            '<CharactersWithSpaces>1</CharactersWithSpaces><SharedDoc>' .
            'false</SharedDoc><HyperlinksChanged>false</HyperlinksChanged>' .
            '<AppVersion>12.0000</AppVersion></Properties>';
    }

    /**
     * Generate DocPropsCore XML template
     *
     * @access private
     */
    private function generateTemplateDocPropsCore()
    {
        date_default_timezone_set('UTC');
        if ($this->_markAsFinal) {
            $this->_docPropsCoreT =
                '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
                '<cp:coreProperties xmlns:cp="http://schemas.openxmlformats' .
                '.org/package/2006/metadata/core-properties" ' .
                'xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:dcterms' .
                '="http://purl.org/dc/terms/" xmlns:dcmitype="http://purl' .
                '.org/dc/dcmitype/" xmlns:xsi="http://www.w3.org/2001/XML' .
                'Schema-instance"><dc:title>Title</dc:title><dc:subject>' .
                'Subject</dc:subject><dc:creator>2mdc</dc:creator>' .
                '<dc:description>Description</dc:description>' .
                '<cp:lastModifiedBy>user</cp:lastModifiedBy><cp:revision>1' .
                '</cp:revision><dcterms:created xsi:type="dcterms:W3CDTF">' .
                date('c') . '</dcterms:created><dcterms:modified ' .
                'xsi:type="dcterms:W3CDTF">' . date('c') .
                '</dcterms:modified><cp:contentStatus>Final' .
                '</cp:contentStatus></cp:coreProperties>';
        } else {
            $this->_docPropsCoreT =
                '<?xml version="1.0" encoding="UTF-8" standalone="yes"?> ' .
                '<cp:coreProperties xmlns:cp="http://schemas.openxmlformats' .
                '.org/package/2006/metadata/core-properties" ' .
                'xmlns:dc="http://purl.org/dc/elements/1.1/" ' .
                'xmlns:dcterms="http://purl.org/dc/terms/" ' .
                'xmlns:dcmitype="http://purl.org/dc/dcmitype/" ' .
                'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">' .
                '<dc:title>Title</dc:title><dc:subject>Subject</dc:subject>' .
                '<dc:creator>2mdc</dc:creator><dc:description>Description' .
                '</dc:description><cp:lastModifiedBy>user' .
                '</cp:lastModifiedBy><cp:revision>1</cp:revision>' .
                '<dcterms:created xsi:type="dcterms:W3CDTF">' . date('c') .
                '</dcterms:created><dcterms:modified xsi:type="dcterms:W3CDTF' .
                '">' . date('c') . '</dcterms:modified></cp:coreProperties>';
        }
    }

    /**
     * Generate DocPropsCustom XML template
     *
     * @access private
     */
    private function generateTemplateDocPropsCustom()
    {
        $this->_docPropsCustomT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Properties xmlns="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/custom-properties" xmlns:vt="http://' .
            'schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">' .
            '<property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" ' .
            'pid="2" name="_MarkAsFinal"><vt:bool>true</vt:bool></property>' .
            '</Properties>';
    }

    /**
     * Generate RelsRels XML template
     *
     * @access private
     */
    private function generateTemplateRelsRels()
    {
        $this->_relsRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/package/' .
            '2006/relationships">' .
            $this->generateRELATIONSHIP(
                'rId3', 'extended-properties', 'docProps/app.xml'
            ) .
            '<Relationship Id="rId2" Type="http://schemas.openxmlformats' .
            '.org/package/2006/relationships/metadata/core-properties"' .
            ' Target="docProps/core.xml"/>' .
            $this->generateRELATIONSHIP(
                'rId1', 'officeDocument', 'word/document.xml'
            );
        if ($this->_markAsFinal) {
            $this->_relsRelsT .=
                '<Relationship Id="rId4" Type="http://schemas' .
                '.openxmlformats.org/officeDocument/2006/relationships/' .
                'custom-properties" Target="docProps/custom.xml"/>';
        }
        $this->_relsRelsT .= '</Relationships>';
    }

    /**
     * Generate WordDocument XML template
     *
     * @access private
     */
    private function generateTemplateWordDocument()
    {
        $arrArgs = func_get_args();
        //$this->generateSECTPR($arrArgs[0]);
        $this->_wordDocumentC .= $this->_sectPr->saveXML($this->_sectPr->documentElement);//FIXME: I am insertying by hand the sections of the base template
        if (!empty($this->_wordHeaderC)) {
            $this->_wordDocumentC = str_replace(
                '__GENERATEHEADERREFERENCE__',
                '<' . CreateDocx::NAMESPACEWORD . ':headerReference ' .
                CreateDocx::NAMESPACEWORD . ':type="default" r:id="rId' .
                $this->_idWords['header'] . '"></' .
                CreateDocx::NAMESPACEWORD . ':headerReference>',
                $this->_wordDocumentC
            );
        }
        if (!empty($this->_wordFooterC)) {
            $this->_wordDocumentC = str_replace(
                '__GENERATEFOOTERREFERENCE__',
                '<' . CreateDocx::NAMESPACEWORD . ':footerReference ' .
                CreateDocx::NAMESPACEWORD . ':type="default" r:id="rId' .
                $this->_idWords['footer'] . '"></' .
                CreateDocx::NAMESPACEWORD . ':footerReference>',
                $this->_wordDocumentC
            );
        }
        $this->_wordDocumentT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':document xmlns:ve=' .
            '"http://schemas.openxmlformats.org/markup-compatibility/2006" ' .
            'xmlns:o="urn:schemas-microsoft-com:office:office"' .
            ' xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006' .
            '/relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml"'.
            ' xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas' .
            '.microsoft.com/office/word/2006/wordml">' .
            $this->_background.
            '<' . CreateDocx::NAMESPACEWORD . ':body>' .
            $this->_wordDocumentC .
            '</' . CreateDocx::NAMESPACEWORD . ':body>' .
            '</' . CreateDocx::NAMESPACEWORD . ':document>';
    }

    /**
     * Generate WordEndnotes XML template
     *
     * @access private
     */
    private function generateTemplateWordEndnotes()
    {
        $this->_wordEndnotesT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':endnotes xmlns:ve' .
            '="http://schemas.openxmlformats.org/markup-compatibility/2006" ' .
            'xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="' .
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:' .
            'vml" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006' .
            '/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas' .
            '.microsoft.com/office/word/2006/wordml">' .
            $this->_wordEndnotesC .
            '</' . CreateDocx::NAMESPACEWORD . ':endnotes>';
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Endnotes.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'endnotes', 'endnotes.xml'
        );
        $this->generateOVERRIDE(
            '/word/endnotes.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.endnotes+xml'
        );
    }

    /**
     * Generate WordFontTable XML template
     *
     * @access private
     */
    private function generateTemplateWordFontTable()
    {
        $this->_wordFontTableT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':fonts xmlns:r="http://' .
            'schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main">' . $this->_wordFontTableC .
            '</' . CreateDocx::NAMESPACEWORD . ':fonts>';
    }

    /**
     * Generate WordFooter XML template
     *
     * @access private
     */
    private function generateTemplateWordFooter()
    {
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Footer.', 'debug');
        $this->_idWords['footer'] = self::$intIdWord;
        $this->_wordFooterT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
            <' . CreateDocx::NAMESPACEWORD . ':ftr xmlns:ve' .
            '="http://schemas.openxmlformats.org/markup-compatibility/' .
            '2006" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns' .
            ':r="http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml' .
            '" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas' .
            '.microsoft.com/office/word/2006/wordml">' . $this->_wordFooterC .
            '</' . CreateDocx::NAMESPACEWORD . ':ftr>';
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'footer', 'footer.xml'
        );

        return 'rId' . self::$intIdWord;
    }

    /**
     * Generate WordFootnotes XML template
     *
     * @access private
     */
    private function generateTemplateWordFootnotes()
    {
        $this->_wordFootnotesT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':footnotes xmlns:ve="' .
            'http://schemas.openxmlformats.org/markup-compatibility/2006" ' .
            'xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="' .
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:' .
            'vml" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006' .
            '/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas.microsoft' .
            '.com/office/word/2006/wordml">' . $this->_wordFootnotesC .
            '</' . CreateDocx::NAMESPACEWORD . ':footnotes>';
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Footnotes.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'footnotes', 'footnotes.xml'
        );
        $this->generateOVERRIDE(
            '/word/footnotes.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.footnotes+xml'
        );
    }

    /**
     * Generate WordHeader XML template
     *
     * @access private
     */
    private function generateTemplateWordHeader()
    {
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Header.', 'debug');
        $this->_idWords['header'] = self::$intIdWord;
        $this->_wordHeaderT = '<?xml version="1.0" encoding="UTF-8" ' .
            'standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD .
            ':hdr xmlns:ve="http://schemas.openxmlformats.org/markup' .
            '-compatibility/2006" xmlns:o="urn:schemas-microsoft-com:' .
            'office:office" xmlns:r="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/relationships" xmlns:m="http://schemas' .
            '.openxmlformats.org/officeDocument/2006/math" xmlns:v="urn:' .
            'schemas-microsoft-com:vml" xmlns:wp="http://schemas' .
            '.openxmlformats.org/drawingml/2006/wordprocessingDrawing" ' .
            'xmlns:w10="urn:schemas-microsoft-com:office:word" xmlns:w="' .
            'http://schemas.openxmlformats.org/wordprocessingml/2006/' .
            'main" xmlns:wne="http://schemas.microsoft.com/office/word/' .
            '2006/wordml"> ' . $this->_wordHeaderC .
            '</' . CreateDocx::NAMESPACEWORD . ':hdr>';
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'header', 'header.xml'
        );
        return 'rId' . self::$intIdWord;
    }

    /**
     * Generate WordNumbering XML template
     *
     * @access private
     */
    private function generateTemplateWordNumbering()
    {
        $this->_wordNumberingT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<w:numbering xmlns:ve="http://schemas.openxmlformats' .
            '.org/markup-compatibility/2006" xmlns:o="urn:schemas-' .
            'microsoft-com:office:office" xmlns:r="http://schemas' .
            '.openxmlformats.org/officeDocument/2006/relationships" ' .
            'xmlns:m="http://schemas.openxmlformats.org/officeDocument/' .
            '2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:' .
            'wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com' .
            ':office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas.' .
            'microsoft.com/office/word/2006/wordml"><w:abstractNum w:'
            . 'abstractNumId="0"><w:nsid w:val="713727AE"/><w:multiLevelType' .
            ' w:val="hybridMultilevel"/><w:tmpl w:val="F0B4B6B8"/>' .
            '<w:lvl w:ilvl="0" w:tplc="0C0A0001"><w:start w:val="1"/>' .
            '<w:numFmt w:val="bullet"/><w:lvlText w:val=""/><w:lvlJc ' .
            'w:val="left"/><w:pPr><w:ind w:left="720" w:hanging="360"/>' .
            '</w:pPr><w:rPr><w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" ' .
            'w:hint="default"/></w:rPr></w:lvl><w:lvl w:ilvl="1" ' .
            'w:tplc="0C0A0003" w:tentative="1"><w:start w:val="1"/>' .
            '<w:numFmt w:val="bullet"/><w:lvlText w:val="o"/><w:lvlJc ' .
            'w:val="left"/><w:pPr><w:ind w:left="1440" w:hanging="360"/>' . '
                </w:pPr><w:rPr><w:rFonts w:ascii="Courier New" w:hAnsi=' .
            '"Courier New" w:cs="Courier New" w:hint="default"/></w:rPr>' .
            '</w:lvl><w:lvl w:ilvl="2" w:tplc="0C0A0005" w:tentative="1">' .
            '<w:start w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText ' .
            'w:val=""/><w:lvlJc w:val="left"/><w:pPr><w:ind w:left="2160" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Wingdings" ' .
            'w:hAnsi="Wingdings" w:hint="default"/></w:rPr></w:lvl><w:lvl ' .
            'w:ilvl="3" w:tplc="0C0A0001" w:tentative="1"><w:start ' .
            'w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val=""/>' .
            '<w:lvlJc w:val="left"/><w:pPr><w:ind w:left="2880" w:hanging=' .
            '"360"/></w:pPr><w:rPr><w:rFonts w:ascii="Symbol" w:hAnsi=' .
            '"Symbol" w:hint="default"/></w:rPr></w:lvl><w:lvl w:ilvl="4" ' .
            'w:tplc="0C0A0003" w:tentative="1"><w:start w:val="1"/>' .
            '<w:numFmt w:val="bullet"/><w:lvlText w:val="o"/><w:lvlJc ' .
            'w:val="left"/><w:pPr><w:ind w:left="3600" w:hanging="360"/>' .
            '</w:pPr><w:rPr><w:rFonts w:ascii="Courier New" w:hAnsi=' .
            '"Courier New" w:cs="Courier New" w:hint="default"/></w:rPr>' .
            '</w:lvl><w:lvl w:ilvl="5" w:tplc="0C0A0005" w:tentative="1">' .
            '<w:start w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText ' .
            'w:val=""/><w:lvlJc w:val="left"/><w:pPr><w:ind w:left="4320" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Wingdings" ' .
            'w:hAnsi="Wingdings" w:hint="default"/></w:rPr></w:lvl><w:lvl ' .
            'w:ilvl="6" w:tplc="0C0A0001" w:tentative="1"><w:start ' .
            'w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val=""/>' .
            '<w:lvlJc w:val="left"/><w:pPr><w:ind w:left="5040" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Symbol" ' .
            'w:hAnsi="Symbol" w:hint="default"/></w:rPr></w:lvl><w:lvl ' .
            'w:ilvl="7" w:tplc="0C0A0003" w:tentative="1"><w:start ' .
            'w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val="o"/>' .
            '<w:lvlJc w:val="left"/><w:pPr><w:ind w:left="5760" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Courier New" ' .
            'w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>' .
            '</w:rPr></w:lvl><w:lvl w:ilvl="8" w:tplc="0C0A0005" ' .
            'w:tentative="1"><w:start w:val="1"/><w:numFmt w:val="bullet"' .
            '/><w:lvlText w:val=""/><w:lvlJc w:val="left"/><w:pPr><w:ind ' .
            'w:left="6480" w:hanging="360"/></w:pPr><w:rPr><w:rFonts ' .
            'w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>' .
            '</w:rPr></w:lvl></w:abstractNum><w:num w:numId="1">' .
            '<w:abstractNumId w:val="0"/></w:num></w:numbering>';
    }

    /**
     * Generate WordNumbering XML template
     *
     * @access private
     */
    private function generateTemplateWordNumberingStyles()
    {
        $this->_wordNumberingT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<w:numbering xmlns:ve="http://schemas.openxmlformats' .
            '.org/markup-compatibility/2006" xmlns:o="urn:schemas-' .
            'microsoft-com:office:office" xmlns:r="http://schemas' .
            '.openxmlformats.org/officeDocument/2006/relationships" ' .
            'xmlns:m="http://schemas.openxmlformats.org/officeDocument/' .
            '2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:' .
            'wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com' .
            ':office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas.' .
            'microsoft.com/office/word/2006/wordml"><w:abstractNum w:'
            . 'abstractNumId="0"><w:nsid w:val="713727AE"/><w:multiLevelType' .
            ' w:val="hybridMultilevel"/><w:tmpl w:val="F0B4B6B8"/>' .
            $this->_wordDocumentStyles . '</w:abstractNum><w:num w:numId="1">' .
            '<w:abstractNumId w:val="0"/></w:num></w:numbering>';
    }

    /**
     * Generate WordRelsDocumentRels XML template
     *
     * @access private
     */
    private function generateTemplateWordRelsDocumentRels()
    {
        $this->_wordRelsDocumentRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/' .
            'package/2006/relationships">' . $this->_wordRelsDocumentRelsC .
            '</Relationships>';
    }

    /**
     * Generate WordRelsFooterRels XML template
     *
     * @access private
     */
    private function generateTemplateWordRelsFooterRels()
    {
        $this->_wordRelsFooterRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/' .
            'package/2006/relationships">' . $this->_wordRelsFooterRelsC .
            '</Relationships>';
    }

    /**
     * Generate WordRelsHeaderRels XML template
     *
     * @access private
     */
    private function generateTemplateWordRelsHeaderRels()
    {
        $this->_wordRelsHeaderRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/' .
            'package/2006/relationships">' . $this->_wordRelsHeaderRelsC .
            '</Relationships>';
    }

    /**
     * Generate WordSettings XML template
     *
     * @access private
     */
    private function generateTemplateWordSettings()
    {
        $this->_wordSettingsT = $this->_wordSettingsC;
    }

    /**
     * Generate WordStyles XML template
     *
     * @access private
     */
    private function generateTemplateWordStyles()
    {
        $this->_wordStylesT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?><' .
            CreateDocx::NAMESPACEWORD . ':styles xmlns:r="http://' .
            'schemas.openxmlformats.org/officeDocument/2006/relationships' .
            '" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/' .
            '2006/main">' . $this->_wordStylesC .
            '</' . CreateDocx::NAMESPACEWORD . ':styles>';
    }

    /**
     * Generate WordThemeTheme1 XML template
     *
     * @access private
     */
    private function generateTemplateWordThemeTheme1()
    {
        $this->addTheme($this->_defaultFont);
        $this->_wordThemeThemeT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?><' .
            CreateTheme1::NAMESPACEWORD . ':theme xmlns:a="http://' .
            'schemas.openxmlformats.org/drawingml/2006/main" name="' .
            'Tema de Office">' . $this->_wordThemeThemeC .
            '</' . CreateTheme1::NAMESPACEWORD . ':theme>';
    }

    /**
     * Generate WordWebSettings XML template
     *
     * @access private
     */
    private function generateTemplateWordWebSettings()
    {
        $this->_wordWebSettingsT = $this->_wordWebSettingsC;
    }

    /**
     * Generates a TitlePg element in SectPr
     *
     * @access private
     */
    private function generateTitlePg()
    {
        $foundNodes = $this->_sectPr->documentElement->getElementsByTagName('w:TitlePg');
        if($foundNodes->length == 0){
            $newSectNode = '<w:titlePg xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />';
            $sectNode = $this->_sectPr->createDocumentFragment();
            $sectNode->appendXML($newSectNode);
            $refNode =$this->_sectPr->documentElement->appendChild($sectNode);
        }
    }

    /**
     * To add support of sys_get_temp_dir for PHP versions under 5.2.1
     *
     * @access private
     * @return string
     */
    public static function getTempDir() {
        if ( !function_exists('sys_get_temp_dir')) {
            function sys_get_temp_dir() {
                if ($temp = getenv('TMP')) {
                    return $temp;
                }
                if ($temp = getenv('TEMP')) {
                    return $temp;
                }
                if ($temp = getenv('TMPDIR')) {
                    return $temp;
                }
                $temp = tempnam(__FILE__,'');
                if (file_exists($temp)) {
                    unlink($temp);
                    return dirname($temp);
                }
                return null;
            }
        } else {
            return sys_get_temp_dir();
        }
    }

    /**
     * Parse path dir
     *
     * @access private
     * @param string $dir Directory path
     */
    private function parsePath($dir)
    {
        $slash = 0;
        $path = '';
        if (($slash = strrpos($dir, '/')) !== false) {
            $slash += 1;
            $path = substr($dir, 0, $slash);
        }
        $punto = strpos(substr($dir, $slash), '.');

        $nombre = substr($dir, $slash, $punto);
        $extension = substr($dir, $punto + $slash + 1);
        return array(
            'path' => $path, 'nombre' => $nombre, 'extension' => $extension
        );
    }

     /**
     * Delete a file or recursively delete a directory
     *
     * @param string $str path to file or directory
     */
    private function recursiveDelete($str){
        if(is_file($str)){
            return @unlink($str);
        }
        elseif(is_dir($str)){
            $scan = glob(rtrim($str,'/').'/*');
            foreach($scan as $index=>$path){
                $this->recursiveDelete($path);
            }
            return @rmdir($str);
        }
    }


     /**
     *
     * Adds directory contents recursively into a zip.
     *
     * @param string $fileName. The path to the dir to add.
     *
     * @param string $myZip. The zip where the contents of the dir should be added.
     *
     */
    private function recursiveInsert($myZip, $fileName, $basePath){
         $length = strlen($basePath);
         if(is_dir($fileName)){
            $contentsDir = scandir($fileName);
            foreach($contentsDir as $element){
              if($element != "." && $element !=".."){
                 $this->recursiveInsert($myZip, $fileName."/".$element, $basePath);
                 }
            }
         }else{
            $newName = substr($fileName, $length + 1);
            $myZip->addFile($fileName, $newName);
         }
     }

     /**
     *
     * Includes data in the setting.xml file.
     *
     * @param array $settings. The string with the nodes that should be included in the settings.xml file.
     *
     */
    private function includeSettings($data){
        try{
            $baseSettings = $this->_baseTemplateZip->getFromName('word/settings.xml');
            if ($baseSettings == '') {
        throw new Exception('Error while extracting the settings.xml file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $settingsDoc = new DOMDocument();
        $settingsDoc->loadXML($baseSettings);
        $settings = $settingsDoc->documentElement;

        foreach($data as $key => $value){
            $newNode = $settingsDoc->createDocumentFragment();
            $newNode->appendXML($value);
            $settings->appendChild($newNode);
        }

        $settingsHandler = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
        fwrite($settingsHandler, $settingsDoc->saveXML());
        fclose($documentHandler);
    }
}
