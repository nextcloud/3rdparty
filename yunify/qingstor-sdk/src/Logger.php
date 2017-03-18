<?php
// +-------------------------------------------------------------------------
// | Copyright (C) 2016 Yunify, Inc.
// +-------------------------------------------------------------------------
// | Licensed under the Apache License, Version 2.0 (the "License");
// | you may not use this work except in compliance with the License.
// | You may obtain a copy of the License in the LICENSE file, or at:
// |
// | http://www.apache.org/licenses/LICENSE-2.0
// |
// | Unless required by applicable law or agreed to in writing, software
// | distributed under the License is distributed on an "AS IS" BASIS,
// | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// | See the License for the specific language governing permissions and
// | limitations under the License.
// +-------------------------------------------------------------------------

namespace QingStor\SDK;

use Psr\Log\LogLevel;

class Logger extends \Katzgrau\KLogger\Logger
{
    private static $_instance = null;

    public static function getInstance($logLevels = LogLevel::WARNING)
    {
        if (is_null(self::$_instance)) {
            switch ($logLevels) {
                case 'debug':
                    $logLevels = LogLevel::DEBUG;
                    break;
                case 'info':
                    $logLevels = LogLevel::INFO;
                    break;
                case 'warn':
                    $logLevels = LogLevel::WARNING;
                    break;
                case 'error':
                    $logLevels = LogLevel::ERROR;
                    break;
                case 'fatal':
                    $logLevels = LogLevel::CRITICAL;
                    break;
            }
            self::$_instance = new self(
                'php://stdout',
                $logLevels
            );
        }

        return self::$_instance;
    }

    public function __clone()
    {
        die('Clone is not allowed.'.E_USER_ERROR);
    }
}
