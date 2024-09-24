<?php
/**
 * libphonenumber-for-php-lite data file
 * This file has been @generated from libphonenumber data
 * Do not modify!
 * @internal
 */

return [
    'id' => 'QA',
    'countryCode' => 0,
    'generalDesc' => [
        'pattern' => '[129]\\d{2,4}',
        'posLength' => [
            3,
            4,
            5,
        ],
    ],
    'tollFree' => [
        'pattern' => '99\\d',
        'example' => '990',
        'posLength' => [
            3,
        ],
    ],
    'premiumRate' => [
        'pattern' => '900',
        'example' => '900',
        'posLength' => [
            3,
        ],
    ],
    'emergency' => [
        'pattern' => '999',
        'example' => '999',
        'posLength' => [
            3,
        ],
    ],
    'shortCode' => [
        'pattern' => '9(?:00|[19]\\d)|(?:1|20|9[27]\\d)\\d\\d',
        'example' => '100',
    ],
    'standardRate' => [
        'posLength' => [
            -1,
        ],
    ],
    'carrierSpecific' => [
        'posLength' => [
            -1,
        ],
    ],
    'smsServices' => [
        'posLength' => [
            -1,
        ],
    ],
    'internationalPrefix' => '',
    'numberFormat' => [],
];
