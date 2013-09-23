<?php
/**
 * Generate a DOCX file
 *
 * @category   Phpdocx
 * @package    config
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */

/**
 * The default base template folder
 */
define('PHPDOCX_BASE_FOLDER', dirname(__FILE__) . '/../templates/');
/**
 * The default base template
 * WARNING: if you choose to change this default template you should make sure 
 * that certain required styles in createDocx for formatting are exported
 */
define('PHPDOCX_BASE_TEMPLATE', PHPDOCX_BASE_FOLDER . 'phpdocxBaseTemplate.docx');
/**
 * The default path to the dompdf dir
 */
define('PHPDOCX_DIR_DOMPDF', PHPDOCX_BASE_FOLDER . '/../pdf');
/**
 * The default path to the HTML parser
 */
define('PHPDOCX_DIR_PARSER', PHPDOCX_BASE_FOLDER . '/../lib/dompdfParser');
/**
 * The allowed file extensions for HTML2WordML conversion
 */
define('PHPDOCX_ALLOWED_IMAGE_EXT', 'gif,png,jpg,jpeg,bmp');

/** 
 * properties arrays
 */

$rProperties = array(
                'rStyle' => 'val', //Represents a character style for this run
                'rFonts' => array( //Represents the fonts for this run
                            'hint', //Hint to Word as to which font to use for display
                            'ascii', //ASCII font
                            'h-ansi', //High ANSI font
                            'eastAsia', //Font used for East Asian characters
                            'cs', //Font used for complex scripts
                            'asciiTheme', //ASCII theme font
                            'hAnsiTheme', //High ANSI theme font
                            'eastAsiaTheme', //East Asian theme font
                            'csTheme' //complex scripts theme font
                            ),
                'b' => 'val', //Sets Latin and Asian characters to bold
                'bCs' => 'val', //Sets complex scripts characters to bold
                'i' => 'val', //Sets Latin and Asian characters to italic
                'iCs' => 'val', //Sets complex scripts characters to italic
                'caps' => 'val', //Formats lowercase text as capital letters. Does not affect numbers, punctuation, non-alphabetic characters, or uppercase letters
                'smallCaps' => 'val', //Formats lowercase text as capital letters and reduces their size. Does not affect numbers, punctuation, non-alphabetic characters, or uppercase letters
                'strike' => 'val', //Draws a line through the text
                'dstrike' => 'val', //Draws a double line through the text
                'outline' => 'val', //Displays the inner and outer borders of each character
                'shadow' => 'val', //Adds a shadow behind the text, beneath and to the right of the text
                'emboss' => 'val', //Makes text appear as if it is raised off the page in relief
                'imprint' => 'val', //Makes selected text appear to be imprinted or pressed into page (also referred to as engrave)
                'noProof' => 'val', //Formats the text so that spelling and grammar errors are ignored in this run
                'snapToGrid' => 'val', //Sets the number of characters per line to match the number of characters specified in the docGrid element of the current section's properties
                'vanish' => 'val', //Prevents the text in this run from being displayed or printed
                'webHidden' => 'val', //Prevents the text in this run from being displayed when this document is saved as a Web page
                'color' => 'val', //Specifies either an automatic color or a hexadecimal color code for this run
                'spacing' => 'val', //Represents the amount in twips by which the spacing between characters is expanded or condensed
                'w' => 'val', //Stretches or compresses text horizontally as a percentage of its current size
                'kern' => 'val', //Represents the smallest font size (in half-points) for which kerning should be automatically adjusted
                'position' => 'val', //Represents the amount (in half-points) by which text should be raised or lowered in relation to the baseline
                'sz' => 'val', //Represents the font size (in half-points) for the Asian and Latin fonts in this run
                'szCs' => 'val', //Represents the font size (in half points) for complex script fonts in this run
                'highlight' => 'val', //Marks text as highlighted so it stands out from the surrounding text
                'u' => 'val', //Represents the underline formatting for this run
                'effect' => 'val', //Represents the animated text effect for this run
                'bdr' => array( //Represents the border for characters in this run
                         'val', //Border-style values
                         'color', //Border color (hexadecimal
                         'sz', //Border width
                         'space', //Border space in eighths of a point 
                         'shadow', //Value indicating whether the border has a shadow
                         'frame' //Value indicating whether to create a frame effect by reversing the border
                         ), 
                'shd' => array( //Represents the shading for characters in this run
                         'val', //Shading-style values
                         'color', //Foreground-shading color value (hexadecimal)
                         'fill' //Background-fill color value
                         ), 
                'fitText' => array( //Represents the width of the space that this run to fit into
                             'val', //Width in twips of space into which a run of text should fit
                             'id' //Unique internal ID that associates multiple runs of fit text
                             ), 
                'vertAlign' => 'val', //Adjusts the vertical position of the text relative to the baseline and changes the font size if possible. To raise or lower the text without reducing the font size, use the position element
                'rtl' => 'val', //Sets the alignment and reading order for this run to right-to-left
                'cs' => 'val', //Specifies if text in this run is complex scripts text
                'em' => 'val', //Sets the type of emphasis mark for this run
                'hyphen' => 'val', //Represents the hyphenation style for this run
                'lang' => array( //Represents the languages for this run
                          'val', //Latin Language
                          'eastAsia', //East Asian Language
                          'bidi' //Complex Script Language
                          ), 
                'eastAsianLayout' =>  array( //Represents special Asian Layout formatting properties
                                  'id', //Unique internal ID that associates multiple runs of Asian text
                                  'combine', //Value indicating whether to combine lines or letters
                                  'combine-brackets', //Bracket style to put around combined text
                                  'vert', //Rotation value for Asian half-width characters so that they appear properly as vertical text 
                                  'vert-compress' //Compression value for the rotated text so it fits within one character unit
                                  ), 
                'specVanish' => 'val', //Represents the special hidden property that makes text in this run always hidden
                'oMath' => 'val', //Office Open XML Math: on, off
                 );

$pProperties = array(
                'pStyle' => 'val', //Represents paragraph style
                'keepNext' => 'val', //Represents Keep with Next Paragraph option: Prevents a page break between this paragraph and the next
                'keepLines' => 'val', //Represents Keep Lines Together option: Prevents a page break in this paragraph
                'pageBreakBefore' => 'val', //Represents Page Break Before option: Forces a page break before this paragraph
                'framePr' => array( //Represents text frame and drop cap properties
                                   'drop-cap', //Position for a drop cap
                                   'lines', //Lines to drop for a drop cap
                                   'w', //Frame width
                                   'h', //Frame heigth
                                   'vspace', //Distance in twips between frame and text above and below the frame
                                   'hspace', //Distance in twips between frame and text to the right and left of the frame 
                                   'wrap', //Text wrapping (valid: none and around)
                                   'hanchor', //Point from which to measure horizontal position/alignment
                                   'vanchor', //Point from which to measure vertical position/alignment
                                   'x', //Horizontal position in twips
                                   'x-align', //Horizontal alignment (overrides position)
                                   'y', //Vertical position in twips
                                   'y-align', //Verticalalignment (overrides position)
                                   'h-rule', //Sets how should height (h) be interpreted 
                                   'anchor-lock' //Locks the anchor of the frame to the paragraph that currently contains it
                                   ),
                'widowControl' => 'val', //Represents Widow/Orphan Control option: Prevents Word from printing the last line of a paragraph by itself at the top of the page (widow) or the first line of a paragraph at the bottom of a page (orphan)
                'numPr' => array( //Numbering definition of the associated list
                                 'ilvl'=> array( //Numbering level
                                                'val' //Decimal number
                                                ),
                                 'mumId'=> array( //Numbering definition
                                                'val' //Decimal number
                                                ),
                                 'numberingChange'=> array( //Previous paragraph numbering properties
                                                'id', //Annotation identifier  
                                                'author', //Annotation author 
                                                'date', //Annotation date 
                                                'original' //Previous numbering value
                                                ),
                                 'ins'=> array( //Inserted numbering properties
                                                'id', //Annotation identifier  
                                                'author', //Annotation author 
                                                'date' //Annotation date 
                                                )
                                 ),
                'supressLineNumbers' => 'val', //Prevents line numbers from appearing next to paragraph. This setting has no effect in documents or sections with no line number
                'pBdr' => array( //Represents borders for the paragraph
                                'top'=> array( //Represents top border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'left'=> array( //Represents left border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'bottom'=> array( //Represents bottom border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'right'=> array( //Represents right border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'between'=> array( //Represents paragraph border between identical paragraphs
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'bar'=> array( //Represents paragraph border between facing pages
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              )
                                ),	
                'shd' => array( //Represents paragraph shading
                         'val', //Shading-style values
                         'color', //Foreground-shading color value (hexadecimal)
                         'fill' //Background-fill color value
                         ),
                'tabs' => array( //Represents tab stop list
                                'tab' => array( //Represents a tab stop. There could be unlimited ocurraeces of this element
                                               'val', //Sets tab alignment (or clear)
                                               'leader', //Style of the empty space in front of the tab
                                               'pos' //sets position
                                               )
                                ),
                'suppressAutoHyphens' => 'val', //Prevents automatic hyphenation
                'kinsoku' => 'val', //Use East Asian typography and line-breaking rules to determine which characters begin and end a line on a page (Asian Typography option)
                'wordWrap' => 'val', //Allows a line to break in the middle of a Latin word (Asian Typography option)
                'overflowPunct' => 'val', //Allows punctuation to continue one character beyond the alignment of other lines in the paragraph. If you do not use this option, all lines and punctuation must be perfectly aligned (Asian Typography option)
                'topLinePunct' => 'val', //Allows punctuation to compress at the start of a line, which lets subsequent characters move in closer (Asian Typography option)
                'autoSpaceDE' => 'val',	//Automatically adjusts character spacing between East Asian and Latin text (Asian Typography option)
                'autoSpaceDN' => 'val', //Automatically adjusts character spacing between East Asian text and numbers (Asian Typography option)
                'bidi' => 'val', //Sets the alignment and reading order for a paragraph to right-to-left
                'adjustRightInd' => 'val', //Automatically adjusts the right indent when you are using the document grid
                'snapToGrid' => 'val', //Aligns text to document grid (when grid is defined)
                'spacing' => array( //Represents spacing between lines and paragraphs
                                   'before', //Space in twips above paragraph
                                   'before-lines', //Number of lines before paragraph (when using character units)
                                   'before-autospacing', //Sets whether space/lines before a paragraph is automatic
                                   'after', //Space in twips below paragraph
                                   'after-lines', //Number of lines after paragraph (when using character units)
                                   'after-autospacing', //Sets whether space/lines after a paragraph is automatic
                                   'line', //Vertical spacing in twips between lines of text
                                   'line-rule' //Specifies interpretation of line attribute 
                                   ),	
                'ind' => array( //Represents paragraph indentation
                               'left', //Space in twips between left margin and text. Negative values move text into margin
                               'left-chars', //Number of character spaces between left margin and text (when using character units). Negative values move text into margin 
                               'right', //Space in twips between text and right margin. Negative values move text into margin
                               'right-chars', //Number of character spaces between text and right margin (when using character units). Negative values move text into margin
                               'hanging', //Hanging indent in twips for all lines after first
                               'hanging-chars', //Number of character spaces hanging indent for all lines after first (when using character units)
                               'first-line', //Indent in twips for first line only (cannot be used with hanging attribute)
                               'first-line-chars' //Number of character spacing indent for first line only (cannot be used with hanging-chars attribute) 
                               ),	
                'contextualSpacing' => 'val', //Specifies not to add space between paragraphs of the same style
                'mirrorIndents' =>  'val', //Use left/right indents as inside/outside indents: on, off
                'suppressOverlap' => 'val', //Specifies not to allow this frame to overlap
                'jc' => 'val', //Represents paragraph alignment: none
                'textDirection' => 'val', //Represents orientation for the paragraph in the current cell, text box, or text frame
                'textAlignment' => 'val', //Determines the vertical alignment of all text in a line (Asian Typography option)
                'textboxTightWrap' => 'val', //Allow surrounding paragraphs to tight wrap to Text Box contents
                'outlineLvl' => 'val', //Represents outline level
                'divId' => 'val', //Represents ID of HTML DIV element this paragraph is currently in
                'cnfStyle' => 'val' //A string representation of a binary bitmask that represents the conditional formatting results for this paragraph within a table cell (left to right): FirstRow, LastRow, FirstColumn, LastColumn, Band1Vertical, Band2Vertical, Band1Horizontal, Band2Horizontal, NE Cell, NW Cell, SE Cell, SW Cell
                //Â¿QUÃ‰ HACEMOS CON ESTO?//rPr	//Represents run properties for the paragraph mark
                //Â¿QUÃ‰ HACEMOS CON ESTO?//sectPr //Represents section properties for section that terminates at this paragraph mark
                );
    
$tblProperties = array( 
                       'tblStyle' => 'val', //Represents the style for this table.
                       'tblpPr' => array( //Represents the table-positioning properties (for floating tables)
                                         'leftFromText', //Distance in twips between the left table border and the surrounding text (for wrapping tables)
                                         'rightFromText', //Distance in twips between the right table border and the surrounding text (for wrapping tables)
                                         'topFromText', //Distance in twips between the top table border and the surrounding text (for wrapping tables)
                                         'bottomFromText', //Distance in twips between bottom-left table border and the surrounding text (for wrapping tables)
                                         'vertAnchor', //Defines how this table is vertically anchored: text, margin, page
                                         'horzAnchor', //Defines how this table is horizontally anchored: taxt, margin, page
                                         'tblpXSpec', //Sets the horizontal alignment (for example, center, left, or right); overrides position set by other formatting options (for example, page layout options)
                                         'tblpX', //Horizontal distance in twips from anchor
                                         'tblpYSpec', //Sets the vertical alignment (for example, top or bottom); overrides position set by other formatting options (for example, page layout options) 
                                         'tblpY' //Vertical distance in twips from anchor
                                         ),	
                       'tblOverlap' => 'val', //Specifies whether this table should avoid overlapping another table during layout. If this tag is not specified, floating tables will be allowed to overlap.
                       'bidiVisual' => 'val', //Specifies that this is not a logical right-to-left table (visual right-to-left, not logical right-to-left).
                       'tblStyleRowBandSize' => 'val',  //When a style specifies the format for a band for rows in a table (a set of contiguous rows), this specifies the number of rows in a band.
                       'tblStyleColBandSize' => 'val',  //When a style specifies the format for a band of columns in a table (a set of contiguous columns), this specifies the number of columns in a band.
                       'tblW' => array( //Represents the preferred width of the table
                                       'w', //Table width. The type of this value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),
                       'jc' => 'val', //Represents the table alignment.
                       'tblCellSpacing' => array( //Represents HTML cellspacing attribute for the table (the spacing between individual cells)
                                       'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),
                       'tblInd' => array( //Represents the width that the table should be indented by
                                       'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),
                       'tblBorders' => array( //Represents the border definitions for the table
                                'top'=> array( //Represents top border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'left'=> array( //Represents left border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'bottom'=> array( //Represents bottom border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'right'=> array( //Represents right border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'insideH'=> array( //Represents the inside horizontal border of a table (this is the border that is applied to all horizontal borders except the top-most and bottom-most borders)
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'insideV'=> array( //Represents the inside vertical border of table (this is the border that is applied to all vertical borders except the left-most and right-most borders)
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              )
                                ),
                       'shd' => array( //Represents the table shading; applies to the cellspacing gaps
                         'val', //Shading-style values
                         'color', //Foreground-shading color value (hexadecimal)
                         'fill' //Background-fill color value
                         ),
                       'tblLayout' => 'type', //Specifies whether the table is of fixed width. If not specified, the contents of the table will be taken in to account during layout.
                       'tblCellMar' => array( //Represents the cell margin defaults for this table's cells
                                             'top' => array( //Represents the top cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            ),
                                             'left' => array( //Represents the left cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            ),
                                             'bottom' => array( //Represents the bottom cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            ),
                                             'right' => array( //Represents the right cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            )
                                             ),
                       'tblLook' => 'val', //Specifies what aspects of the table styles should be included. This is a bitmask of options: 0x0020=Apply header row formatting; 0x0040=Apply last row formatting; 0x0080=Apply header column formatting; 0x0100=Apply last column formatting.
    
                );

$trProperties = array(
                      'cnfStyle' => 'val', //A string representation of a binary bitmask representing the conditional formatting results for this table row (left to right): FirstRow, LastRow, FirstColumn, LastColumn, Band1Vertical, Band2Vertical, Band1Horizontal, Band2Horizontal, NE Cell, NW Cell, SE Cell, SW Cell.
                      'divId' => 'val', //Defines what HTML DIV element this row belongs within
                      'gridBefore' => 'val', //Represents the number of grid units consumed before the first cell; assumed to be zero
                      'gridAfter' => 'val', //Represents the number of grid units consumed after the last cell; assumed to be zero
                      'wBefore' => array( //Represents the preferred width before the table row
                                       'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),	
                      'wAfter' => array( //Represents the preferred width after the table row
                                       'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),	
                      'cantSplit' => 'val', //Specifies that a page cannot split this row
                      'trHeight' => array( //Represents the height of this row
                                       'val', //height value
                                       'h-rule' //rule that determines how to use the height value: auto, exact, at-least
                                       ),	
                      'tblHeader' => 'val', //Specifies that this row belongs to the collection of header rows that will repeat at the top of every page and will get any special header row formatting from the table style. If this row is not contiguously connected with the first row of the table (that is, if it isn't either the first row itself, or all of the rows between this row and the first row are marked as header rows), this property will be ignored
                      'tblCellSpacing' => array( //Table row cell spacing
                                       'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),	
                      'jc' => 'val', //Represents the table alignment
                      'hidden' => 'val' //Hidden table row marker
                    );
    
$tcProperties = array(
                      'cnfStyle' => 'val', //A string representation of a binary bitmask representing the conditional formatting results for this table cell (left to right): FirstRow, LastRow, FirstColumn, LastColumn, Band1Vertical, Band2Vertical, Band1Horizontal, Band2Horizontal, NE Cell, NW Cell, SE Cell, SW Cell
                      'tcW' => array( //Represents the preferred width for this cell
                                       'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                       'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                       ),
                      'gridSpan' => 'val', //Represents the number of grid units this cell consumes -- assumed to be 1
                      'hMerge' => 'val', //Specifies whether this cell is part of (or the beginning of) a horizontally merged region: continue, restart
                      'vMerge' => 'val', //Specifies whether this cell is part of (or the beginning of) a vertically merged region: continue, resatrt
                      'tcBorders' => array( //Defines the borders for this cell -- these definitions override the definitions given by the table borders
                                'top'=> array( //Represents top border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'left'=> array( //Represents left border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'bottom'=> array( //Represents bottom border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'right'=> array( //Represents right border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'insideH'=> array( //Represents the horizontal border between two cells. Only used in table-style conditional formatting
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'insideV'=> array( //Represents the vertical border between two cells. Only used in table-style conditional formatting
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'tl2br'=> array( //Defines the top-left to bottom-right diagonal border of the cel
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                'tr2bl'=> array( //Defines the top-right to bottom-left diagonal border of the cel
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              )
                                ),
                      'shd' => array( //Represents the underlying shading for this cell
                         'val', //Shading-style values
                         'color', //Foreground-shading color value (hexadecimal)
                         'fill' //Background-fill color value
                         ),
                      'noWrap' => 'val', //If present, specifies that the contents of this cell should never wrap
                      'tcMar' => array( //Defines the margins for this cell (maps to CSS padding property). Overrides any definitions given in the table properties
                                             'top' => array( //Represents the top cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            ),
                                             'left' => array( //Represents the left cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            ),
                                             'bottom' => array( //Represents the bottom cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            ),
                                             'right' => array( //Represents the right cell margin (maps directly to CSS padding-top property)
                                                            'w', //The real value is dependent on the w:type value; twips or nil means twips; auto means automatic (w is ignored), and pct means 1/50 percent (for example, 5000 = 100%, 4975 = 99.5%, and so on)
                                                            'type' //Determines how to interpret the width: nil, pct, dxa, auto
                                                            )
                                             ),
                      'textDirection' => 'val', //Defines the text flow for this cell
                      'tcFitText' => 'val', //Visually reduces the size of font characters so that all text within the cell fits within the column width. The more text, the smaller the font appears on the screen. The actual font size does not change
                      'vAlign' => 'val',  //Specifies where you want the text in the cells to be aligned, whether it is at the top, center, or bottom   
                      'hideMark' => 'val' //Ignore end of cell marker in row height calculation: on, off
                      );
    
$sectProperies = array(
                       'headerReference' => array ('r:id', 'type'), //Header reference. The type may be: even, default, first
                       'footerReference' => array ('r:id', 'type'), //Footer reference. The type may be: even, default, first
                       'footnotePr' => array( //Represents the footnote properties for this section
                                             'position' => 'val', // Footnote position: value in half-points (1/144 of an inch) that can be positive or negative
                                             'numFmt' => 'val', //Number format for automatically numbered footnotes: decimal, upper-roman,...
                                             'numStart' => 'val', //Starting number or character for the first automatically numbered footnotes
                                             'numRestart' => 'val' //Determines when automatic numbering restarts: continuous, each-sect, each-page                         
                                             ),	
                       'endnotePr' => array( //Represents the endnote properties for this section
                                             'position' => 'val', // Endnote position: value in half-points (1/144 of an inch) that can be positive or negative
                                             'numFmt' => 'val', //Number format for automatically numbered endnotes: decimal, upper-roman,...
                                             'numStart' => 'val', //Starting number or character for the first automatically numbered endnotes
                                             'numRestart' => 'val' //Determines when automatic numbering restarts: continuous, each-sect, each-page                         
                                             ),
                       'type' => 'val', //Represents the section type: next-page, next-column, continuous, even-page, odd-page
                       'pgSz' => array( //Specifies the size and orientation of this page
                                       'w', //Width of the page in twips 
                                       'h', //Height of the page in twips
                                       'orient', //Page orientation: portrait, landscape
                                       'code' //Internal paper code to ensure the proper type is chosen if size matches size of multiple paper types supported by your printer            
                                       ),	
                       'pgMar' => array( //Specifies the page margins
                                        'top', 	//Required. Distance in twips between the top edge of the page and the top of the first line on the page	
                                        'right', //Required. Distance in twips between the right edge of the page and the right end of a line with no right indent	
                                        'bottom', //Required. Distance in twips between the top edge of the page and the top of the first line on the page	
                                        'right', //Required. Distance in twips between the bottom edge of the page and the bottom of the last line on the page	
                                        'left', //Required. Distance in twips between the top edge of the page and the top of the first line on the page	
                                        'right', //Required. Distance in twips between the left edge of the page and the left edge of unindented lines	
                                        'header', //Required. Distance in twips between the top edge of the page and the top of the first line on the page	
                                        'right', //Required. Distance in twips from the top edge of the paper to the top edge of the header	
                                        'footer', //Required. Distance in twips between the top edge of the page and the top of the first line on the page	
                                        'right', //Required. Distance in twips from the bottom edge of the paper to the bottom edge of the footer	
                                        'gutter' //Required. Extra space in twips added to the margin for document binding
                                        ),	
                       'paperSrc' => array( //Specifies where the paper is located in the printer
                                           'first', //Optional. Code for the printer tray from which you want the first page of each section to print	
                                           'other' //Optional. Code for the printer tray from which you want to print the second and subsequent pages in each section
                                           ),
                       'pgBorders' => array( //Specifies the page borders
                                            'z-order', //Optional. Specifies where the page border is positioned relative to intersecting texts and objects: front, back
                                            'display', //Optional. Specifies which pages the page border is printed on: all-pages, first-page, not-first-page 
                                            'offset-from', //Optional: Specifies positioning of page border relative to page margin: page, text
                                            'top'=> array( //Represents top page border
                                              'val', //Border-style values
                                              'color', //Border color (hexadecimal
                                              'sz', //Border width
                                              'space', //Border space in eighths of a point 
                                              'shadow', //Value indicating whether the border has a shadow
                                              'frame' //Value indicating whether to create a frame effect by reversing the border
                                              ),
                                            'left'=> array( //Represents left page border
                                                          'val', //Border-style values
                                                          'color', //Border color (hexadecimal
                                                          'sz', //Border width
                                                          'space', //Border space in eighths of a point 
                                                          'shadow', //Value indicating whether the border has a shadow
                                                          'frame' //Value indicating whether to create a frame effect by reversing the border
                                                          ),
                                            'bottom'=> array( //Represents bottom page border
                                                          'val', //Border-style values
                                                          'color', //Border color (hexadecimal
                                                          'sz', //Border width
                                                          'space', //Border space in eighths of a point 
                                                          'shadow', //Value indicating whether the border has a shadow
                                                          'frame' //Value indicating whether to create a frame effect by reversing the border
                                                          ),
                                            'right'=> array( //Represents right page border
                                                          'val', //Border-style values
                                                          'color', //Border color (hexadecimal
                                                          'sz', //Border width
                                                          'space', //Border space in eighths of a point 
                                                          'shadow', //Value indicating whether the border has a shadow
                                                          'frame' //Value indicating whether to create a frame effect by reversing the border
                                                          )
                                            ),	
                       'lnNumType' => array( //Specifies the line numbering
                                            'count-by',	//Optional. Number to count by	
                                            'start', //Optional. Starting number	
                                            'distance',	//Optional. Distance in twips between the right edge of line numbers and the left edge of the document	
                                            'restart'	//Optional. Resets the line number to the start value: new-page, new-section, continuous                           
                                            ),	
                       'pgNumType' => array( //Specifies the page-numbering options
                                           'fmt', //Optional. Number format: decimal, upper-roman, ...
                                           'start', //Optional. Number to appear on the first page of the section. If left blank, numbering will continue from previous section 
                                           'chap-style', //Optional. Heading style applied to chapter titles in the document. If you are using chapter numbers, this heading style must be used only for chapter headings
                                           'chap-sep' //Optional. Separator character that appears between the chapter and page number                         
                                            ),	
                       'cols' => array( //Specifies the column properties for this section. If all the columns are of the same width, you need only to specify the number of columns (in the num attribute) and the space between columns (in the space attribute)
                                       'equalWidth', //Optional. Specifies whether all columns are of equal width: on, off
                                       'space', //Optional. If all columns are of equal width, it is the amount of space in twips between each column	
                                       'num', //Optional. If all columns are of equal width, it is the number of columns	
                                       'sep', //Optional. Adds a vertical line between columns: on, off
                                       'col' => array( //Represents a column in a section. If all columns are not of equal width, a col element is required for each column and the space and num attributes of the cols element should not exist
                                                      'w', //Colum width in twips
                                                      'space' //Space before following column in twips
                                                      )
                                       ),
                       'formProt' => 'val',  //Turns protection on for this section alone: on, off
                       'vAlign' => 'val', //Sets alignment for text vertically between the top and bottom margins: top, center, both, bottom
                       'noEndnote' => 'val', //Suppresses endnotes that would ordinarily appear at the end of this section: on, off
                       'titlePg' => 'val', //Specifies that the first page of this section is different and will have different headers and footers: on, off
                       'textDirection' => 'val', //Specifies the text flow: lr-tb, tb-rl, bt-lr, lr-tb-v, tb-rl-v
                       'bidi' => 'val',	//Specifies that this section contains bidirectional (complex scripts) text: on, off
                       'rtlGutter' => 'val', //Positions the gutter at the right of the document: on, off
                       'docGrid' => array( //Specifies the document grid
                                          'type', //Optional. Grid type: default, lines, lines-and-chars, snap-to-chars
                                          'line-pitch', //Optional. Line pitch and space between lines. The number of lines per page will automatically be adjusted to fit the space between the lines.	
                                          'char-space'	//Optional. Number of characters per line for a document.
                                          )	    
                      );
