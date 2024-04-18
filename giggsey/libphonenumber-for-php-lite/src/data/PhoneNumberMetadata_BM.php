<?php
/**
 * libphonenumber-for-php-lite data file
 * This file has been @generated from libphonenumber data
 * Do not modify!
 * @internal
 */

return  [
  'generalDesc' =>
   [
    'NationalNumberPattern' => '(?:441|[58]\\d\\d|900)\\d{7}',
    'PossibleLength' =>
     [
      0 => 10,
    ],
    'PossibleLengthLocalOnly' =>
     [
      0 => 7,
    ],
  ],
  'fixedLine' =>
   [
    'NationalNumberPattern' => '441(?:[46]\\d\\d|5(?:4\\d|60|89))\\d{4}',
    'ExampleNumber' => '4414123456',
    'PossibleLengthLocalOnly' =>
     [
      0 => 7,
    ],
  ],
  'mobile' =>
   [
    'NationalNumberPattern' => '441(?:[2378]\\d|5[0-39]|9[02])\\d{5}',
    'ExampleNumber' => '4413701234',
    'PossibleLengthLocalOnly' =>
     [
      0 => 7,
    ],
  ],
  'tollFree' =>
   [
    'NationalNumberPattern' => '8(?:00|33|44|55|66|77|88)[2-9]\\d{6}',
    'ExampleNumber' => '8002123456',
  ],
  'premiumRate' =>
   [
    'NationalNumberPattern' => '900[2-9]\\d{6}',
    'ExampleNumber' => '9002123456',
  ],
  'sharedCost' =>
   [
    'PossibleLength' =>
     [
      0 => -1,
    ],
  ],
  'personalNumber' =>
   [
    'NationalNumberPattern' => '52(?:3(?:[2-46-9][02-9]\\d|5(?:[02-46-9]\\d|5[0-46-9]))|4(?:[2-478][02-9]\\d|5(?:[034]\\d|2[024-9]|5[0-46-9])|6(?:0[1-9]|[2-9]\\d)|9(?:[05-9]\\d|2[0-5]|49)))\\d{4}|52[34][2-9]1[02-9]\\d{4}|5(?:00|2[125-9]|33|44|66|77|88)[2-9]\\d{6}',
    'ExampleNumber' => '5002345678',
  ],
  'voip' =>
   [
    'PossibleLength' =>
     [
      0 => -1,
    ],
  ],
  'pager' =>
   [
    'PossibleLength' =>
     [
      0 => -1,
    ],
  ],
  'uan' =>
   [
    'PossibleLength' =>
     [
      0 => -1,
    ],
  ],
  'voicemail' =>
   [
    'PossibleLength' =>
     [
      0 => -1,
    ],
  ],
  'noInternationalDialling' =>
   [
    'PossibleLength' =>
     [
      0 => -1,
    ],
  ],
  'id' => 'BM',
  'countryCode' => 1,
  'internationalPrefix' => '011',
  'nationalPrefix' => '1',
  'nationalPrefixForParsing' => '([2-9]\\d{6})$|1',
  'nationalPrefixTransformRule' => '441$1',
  'sameMobileAndFixedLinePattern' => false,
  'numberFormat' =>
   [
  ],
  'mainCountryForCode' => false,
  'leadingDigits' => '441',
  'mobileNumberPortableRegion' => true,
];
