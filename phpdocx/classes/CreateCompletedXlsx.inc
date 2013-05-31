<?php

/**
 * Create Completed xlsx for bar/cols, line, radar,... charts
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
class CreateCompletedXlsx extends CreateXlsx
{
    /**
     * @access private
     * @var CreateFooter
     * @static
     */
    private static $_instance = NULL;

    /**
     *
     * @access public
     * @return CreateXlsx
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreateCompletedXlsx();
        }
        return self::$_instance;
    }

	/**
     * Create excel sheet
     *
     * @access public
     * @param string $args[0]
     * @param array $args[1]
     */
	public function createExcelSheet($dats)
    {
        $this->_xml = '';
        $sizeDats = count($dats);
        foreach ($dats as $ind => $data) {
            $sizeCols = count($data);
            break;
        }
        $sizeDats = count($dats);
        $sizeDats--;
        $this->generateWORKSHEET();
        $this->generateDIMENSION($sizeDats, $sizeCols);
        $this->generateSHEETVIEWS();
        $this->generateSHEETVIEW();
        $this->generateSELECTION($sizeDats + $sizeCols);
        $this->generateSHEETFORMATPR();
        $this->generateCOLS();
        $this->generateCOL();
        $this->generateSHEETDATA();
        $row = 1;
        foreach ($dats as $ind => $val) {
            $col = 1;
            $letter = 'A';
            $this->generateROW($row, $sizeCols);
            $this->generateC($letter . $row, '', 's');
            $this->generateV($sizeDats + $sizeCols);
            $letter++;
            foreach ($val as $valores) {
                $this->generateC($letter . $row, '', 's');
                $this->generateV($col - 1);
                $col++;
                $letter++;
            }
            $this->cleanTemplateROW();
            $row++;
            break;
        }
        foreach ($dats as $ind => $val) {
            if ($ind == 'legend')
                continue;
            $this->generateROW($row, $sizeCols);
            $col = 1;
            $letter = 'A';
            $this->generateC($letter . $row, 1, 's');
            $this->generateV($sizeCols + $row - 2);
            $letter++;
            foreach ($val as $valores) {
                $s = '';
                if ($col != $sizeCols)
                    $s = 1;
                $this->generateC($letter . $row, $s);
                $this->generateV($valores);
                $col++;
                $letter++;
            }
            $row++;
            $this->cleanTemplateROW();
        }
        $this->generateROW($row + 1, $sizeCols);
        $row++;
        $this->generateC('B' . $row, 2, 's');
        $this->generateV($sizeDats + $sizeCols + 1);
        $this->generatePAGEMARGINS();
        $this->generateTABLEPARTS();
        $this->generateTABLEPART(1);
        $this->cleanTemplate();
  		return $this->_xml;
    }

    /**
     * Create excel shared strings
     *
     * @param string $args[0]
     * @param string $args[1]
     * @access public
     */
    public function createExcelSharedStrings($dats)
    {
        $this->_xml = '';
        $szDats = count($dats);
        foreach ($dats as $ind => $data) {
            $szCols = count($data);
            break;
        }
        $szDats = count($dats);
        $szDats--;
        $this->generateSST($szDats + $szCols + 2);

        for ($i = 0; $i < $szCols; $i++) {
            $this->generateSI();
            if (!isset($dats['legend'][$i])) {
                $dats['legend'][$i] = '';
            }
            $this->generateT($dats['legend'][$i]);
        }

        foreach ($dats as $ind => $val) {
            if ($ind == 'legend')
                continue;
            $this->generateSI();
            $this->generateT($ind);
        }
        $this->generateSI();
        $this->generateT(' ', 'preserve');

        $msg = 'To change the range size of values,' .
                'drag the bottom right corner';
        $this->generateSI();
        $this->generateT($msg);

        $this->cleanTemplate();
  		return $this->_xml;
    }

    /**
     * Create excel table
     *
     * @access public
     * @param string args[0]
     * @param string args[1]
     */
    public function createExcelTable($dats)
    {
        $this->_xml = '';
        $szDats = count($dats);
        foreach ($dats as $ind => $data) {
            $szCols = count($data);
            break;
        }
        $szDats = count($dats);
        $szDats--;
        $this->generateTABLE($szDats, $szCols);
        $this->generateTABLECOLUMNS($szCols + 1);
        $this->generateTABLECOLUMN(1, ' ');
        for ($i = 0; $i < $szCols; $i++) {
            $this->generateTABLECOLUMN($i + 2, $dats['legend'][$i]);
        }
        $this->generateTABLESTYLEINFO();
        $this->cleanTemplate();
        return $this->_xml;
    }

}