<?php
/**
 * libphonenumber-for-php-lite data file
 * This file has been @generated from libphonenumber data
 * Do not modify!
 * @internal
 */

return [
    'id' => 'SX',
    'countryCode' => 1,
    'generalDesc' => [
        'pattern' => '7215\\d{6}|(?:[58]\\d\\d|900)\\d{7}',
        'posLength' => [
            10,
        ],
        'posLengthLocal' => [
            7,
        ],
    ],
    'fixedLine' => [
        'pattern' => '7215(?:4[2-8]|8[239]|9[056])\\d{4}',
        'example' => '7215425678',
        'posLengthLocal' => [
            7,
        ],
    ],
    'mobile' => [
        'pattern' => '7215(?:1[02]|2\\d|5[034679]|8[014-8])\\d{4}',
        'example' => '7215205678',
        'posLengthLocal' => [
            7,
        ],
    ],
    'tollFree' => [
        'pattern' => '8(?:00|33|44|55|66|77|88)[2-9]\\d{6}',
        'example' => '8002123456',
    ],
    'premiumRate' => [
        'pattern' => '900[2-9]\\d{6}',
        'example' => '9002123456',
    ],
    'sharedCost' => [
        'posLength' => [
            -1,
        ],
    ],
    'personalNumber' => [
        'pattern' => '52(?:3(?:[2-46-9][02-9]\\d|5(?:[02-46-9]\\d|5[0-46-9]))|4(?:[2-478][02-9]\\d|5(?:[034]\\d|2[024-9]|5[0-46-9])|6(?:0[1-9]|[2-9]\\d)|9(?:[05-9]\\d|2[0-5]|49)))\\d{4}|52[34][2-9]1[02-9]\\d{4}|5(?:00|2[125-9]|33|44|66|77|88)[2-9]\\d{6}',
        'example' => '5002345678',
    ],
    'voip' => [
        'posLength' => [
            -1,
        ],
    ],
    'pager' => [
        'posLength' => [
            -1,
        ],
    ],
    'uan' => [
        'posLength' => [
            -1,
        ],
    ],
    'voicemail' => [
        'posLength' => [
            -1,
        ],
    ],
    'noInternationalDialling' => [
        'posLength' => [
            -1,
        ],
    ],
    'internationalPrefix' => '011',
    'nationalPrefix' => '1',
    'nationalPrefixForParsing' => '(5\\d{6})$|1',
    'nationalPrefixTransformRule' => '721$1',
    'numberFormat' => [],
    'leadingDigits' => '721',
    'mobileNumberPortableRegion' => true,
];
