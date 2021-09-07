<?php

declare(strict_types=1);

namespace PackageVersions;

use Composer\InstalledVersions;
use OutOfBoundsException;

class_exists(InstalledVersions::class);

/**
 * This class is generated by composer/package-versions-deprecated, specifically by
 * @see \PackageVersions\Installer
 *
 * This file is overwritten at every run of `composer install` or `composer update`.
 *
 * @deprecated in favor of the Composer\InstalledVersions class provided by Composer 2. Require composer-runtime-api:^2 to ensure it is present.
 */
final class Versions
{
    /**
     * @deprecated please use {@see self::rootPackageName()} instead.
     *             This constant will be removed in version 2.0.0.
     */
    const ROOT_PACKAGE_NAME = 'nextcloud/3rdparty';

    /**
     * Array of all available composer packages.
     * Dont read this array from your calling code, but use the \PackageVersions\Versions::getVersion() method instead.
     *
     * @var array<string, string>
     * @internal
     */
    const VERSIONS          = array (
  'aws/aws-sdk-php' => '3.184.6@0b7187c96ced465d400ad9427157e05ddee68edc',
  'bantu/ini-get-wrapper' => 'v1.0.1@4770c7feab370c62e23db4f31c112b7c6d90aee2',
  'beberlei/assert' => 'v3.3.0@5367e3895976b49704ae671f75bc5f0ba1b986ab',
  'brick/math' => '0.9.1@283a40c901101e66de7061bd359252c013dcc43c',
  'christophwurst/id3parser' => 'v0.1.2@d7f5e9e7db69a24e3111a2033cbdf640f9456f2f',
  'composer/package-versions-deprecated' => '1.11.99.1@7413f0b55a051e89485c5cb9f765fe24bb02a7b6',
  'deepdiver/zipstreamer' => '2.0.0@b8c59647ff34fb97e8937aefb2a65de2bc4b4755',
  'deepdiver1975/tarstreamer' => '2.0.0@ad48505d1ab54a8e94e6b1cc5297bbed72e956de',
  'doctrine/cache' => '1.10.2@13e3381b25847283a91948d04640543941309727',
  'doctrine/dbal' => '3.0.0@ee6d1260d5cc20ec506455a585945d7bdb98662c',
  'doctrine/event-manager' => '1.1.1@41370af6a30faa9dc0368c4a6814d596e81aba7f',
  'doctrine/lexer' => '1.2.1@e864bbf5904cb8f5bb334f99209b48018522f042',
  'egulias/email-validator' => '2.1.25@0dbf5d78455d4d6a41d186da50adc1122ec066f4',
  'fgrosse/phpasn1' => 'v2.2.0@d1978f7abd580f3fc33561e7f71d4c12c7531fad',
  'giggsey/libphonenumber-for-php' => '8.12.25@7d397cbd2e01e78cf79ff347e40a403dbc4c22fa',
  'giggsey/locale' => '1.9@b07f1eace8072ccc61445ad8fbd493ff9d783043',
  'guzzlehttp/guzzle' => '7.3.0@7008573787b430c1c1f650e3722d9bba59967628',
  'guzzlehttp/promises' => '1.4.1@8e7d04f1f6450fef59366c399cfad4b9383aa30d',
  'guzzlehttp/psr7' => '1.8.2@dc960a912984efb74d0a90222870c72c87f10c91',
  'guzzlehttp/uri-template' => 'v0.2.0@db46525d6d8fee71033b73cc07160f3e5271a8ce',
  'icewind/searchdav' => 'v2.0.0@c69806d900c2c9a5954bfabc80178d6eb0d63df4',
  'icewind/streams' => 'v0.7.5@0c6aae16ebdadb257f0bd089c1e1e4cf5e20ddc2',
  'justinrainbow/json-schema' => '5.2.10@2ba9c8c862ecd5510ed16c6340aa9f6eadb4f31b',
  'league/flysystem' => '1.1.3@9be3b16c877d477357c015cec057548cf9b2a14a',
  'league/mime-type-detection' => '1.7.0@3b9dff8aaf7323590c1d2e443db701eb1f9aa0d3',
  'league/uri' => '6.4.0@09da64118eaf4c5d52f9923a1e6a5be1da52fd9a',
  'league/uri-interfaces' => '2.2.0@667f150e589d65d79c89ffe662e426704f84224f',
  'microsoft/azure-storage-blob' => '1.5.2@2475330963372d519387cb8135d6a9cfd42272da',
  'microsoft/azure-storage-common' => '1.5.1@e5738035891546075bd369954e8af121d65ebd6d',
  'mtdowling/jmespath.php' => '2.6.1@9b87907a81b87bc76d19a7fb2d61e61486ee9edb',
  'nextcloud/lognormalizer' => 'v1.0.0@87445d69225c247aaff64643b1fc83c6d6df741f',
  'nikic/php-parser' => 'v4.10.5@4432ba399e47c66624bc73c8c0f811e5c109576f',
  'opis/closure' => '3.6.2@06e2ebd25f2869e54a306dda991f7db58066f7f6',
  'patchwork/jsqueeze' => 'v2.0.5@693d64850eab2ce6a7c8f7cf547e1ab46e69d542',
  'pear/archive_tar' => '1.4.14@4d761c5334c790e45ef3245f0864b8955c562caa',
  'pear/console_getopt' => 'v1.4.3@a41f8d3e668987609178c7c4a9fe48fecac53fa0',
  'pear/pear-core-minimal' => 'v1.10.10@625a3c429d9b2c1546438679074cac1b089116a7',
  'pear/pear_exception' => 'v1.0.2@b14fbe2ddb0b9f94f5b24cf08783d599f776fff0',
  'php-ds/php-ds' => 'v1.3.0@b98396862fb8a13cbdbbaf4d18be28ee5c01ed3c',
  'php-http/guzzle7-adapter' => '1.0.0@fb075a71dbfa4847cf0c2938c4e5a9c478ef8b01',
  'php-http/httplug' => '2.2.0@191a0a1b41ed026b717421931f8d3bd2514ffbf9',
  'php-http/promise' => '1.1.0@4c4c1f9b7289a2ec57cde7f1e9762a5789506f88',
  'php-opencloud/openstack' => 'v3.1.0@7b0eeb63defe533fb802514af3c70855c45eaf1e',
  'phpseclib/phpseclib' => '2.0.32@f5c4c19880d45d0be3e7d24ae8ac434844a898cd',
  'pimple/pimple' => 'v3.4.0@86406047271859ffc13424a048541f4531f53601',
  'psr/container' => '1.1.1@8622567409010282b7aeebe4bb841fe98b58dcaf',
  'psr/event-dispatcher' => '1.0.0@dbefd12671e8a14ec7f180cab83036ed26714bb0',
  'psr/http-client' => '1.0.1@2dfb5f6c5eff0e91e20e913f8c5452ed95b86621',
  'psr/http-factory' => '1.0.1@12ac7fcd07e5b077433f5f2bee95b3a771bf61be',
  'psr/http-message' => '1.0.1@f6561bf28d520154e4b0ec72be95418abe6d9363',
  'psr/log' => '1.1.3@0f73288fd15629204f9d42b7055f72dacbe811fc',
  'punic/punic' => '1.6.5@7bc85ce1137cf52db4d2a6298256a4c4a24da99a',
  'ralouphie/getallheaders' => '3.0.3@120b605dfeb996808c31b6477290a714d356e822',
  'ramsey/collection' => '1.1.1@24d93aefb2cd786b7edd9f45b554aea20b28b9b1',
  'ramsey/uuid' => '4.1.1@cd4032040a750077205918c86049aa0f43d22947',
  'sabre/dav' => '4.1.5@c1afdc77a95efea6ee40c03c45f57c3c0c80ec22',
  'sabre/event' => '5.1.2@c120bec57c17b6251a496efc82b732418b49d50a',
  'sabre/http' => '5.1.1@d0aafede6961df6195ce7a8dad49296b0aaee22e',
  'sabre/uri' => '2.2.1@f502edffafea8d746825bd5f0b923a60fd2715ff',
  'sabre/vobject' => '4.3.5@d8a0a9ae215a8acfb51afc29101c7344670b9c83',
  'sabre/xml' => '2.2.3@c3b959f821c19b36952ec4a595edd695c216bfc6',
  'scssphp/scssphp' => 'v1.4.1@ba86c963b94ec7ebd6e19d90cdab90d89667dbf7',
  'spomky-labs/base64url' => 'v2.0.4@7752ce931ec285da4ed1f4c5aa27e45e097be61d',
  'spomky-labs/cbor-php' => 'v2.0.1@9776578000be884cd7864eeb7c37a4ac92d8c995',
  'stecman/symfony-console-completion' => '0.11.0@a9502dab59405e275a9f264536c4e1cb61fc3518',
  'swiftmailer/swiftmailer' => 'v6.2.7@15f7faf8508e04471f666633addacf54c0ab5933',
  'symfony/console' => 'v4.4.25@a62acecdf5b50e314a4f305cd01b5282126f3095',
  'symfony/event-dispatcher' => 'v4.4.25@047773e7016e4fd45102cedf4bd2558ae0d0c32f',
  'symfony/event-dispatcher-contracts' => 'v1.1.9@84e23fdcd2517bf37aecbd16967e83f0caee25a7',
  'symfony/polyfill-ctype' => 'v1.23.0@46cd95797e9df938fdd2b03693b5fca5e64b01ce',
  'symfony/polyfill-iconv' => 'v1.23.0@63b5bb7db83e5673936d6e3b8b3e022ff6474933',
  'symfony/polyfill-intl-grapheme' => 'v1.23.0@24b72c6baa32c746a4d0840147c9715e42bb68ab',
  'symfony/polyfill-intl-idn' => 'v1.23.0@65bd267525e82759e7d8c4e8ceea44f398838e65',
  'symfony/polyfill-intl-normalizer' => 'v1.23.0@8590a5f561694770bdcd3f9b5c69dde6945028e8',
  'symfony/polyfill-mbstring' => 'v1.23.0@2df51500adbaebdc4c38dea4c89a2e131c45c8a1',
  'symfony/polyfill-php72' => 'v1.23.0@9a142215a36a3888e30d0a9eeea9766764e96976',
  'symfony/polyfill-php73' => 'v1.23.0@fba8933c384d6476ab14fb7b8526e5287ca7e010',
  'symfony/polyfill-php80' => 'v1.23.0@eca0bf41ed421bed1b57c4958bab16aa86b757d0',
  'symfony/process' => 'v4.4.25@cd61e6dd273975c6625316de9d141ebd197f93c9',
  'symfony/routing' => 'v4.4.25@3a3c2f197ad0846ac6413225fc78868ba1c61434',
  'symfony/service-contracts' => 'v2.4.0@f040a30e04b57fbcc9c6cbcf4dbaa96bd318b9bb',
  'symfony/translation' => 'v4.4.25@dfe132c5c6d89f90ce7f961742cc532e9ca16dd4',
  'symfony/translation-contracts' => 'v2.4.0@95c812666f3e91db75385749fe219c5e494c7f95',
  'thecodingmachine/safe' => 'v1.3.3@a8ab0876305a4cdaef31b2350fcb9811b5608dbc',
  'web-auth/cose-lib' => 'v3.3.9@ed172d2dc1a6b87b5c644c07c118cd30c1b3819b',
  'web-auth/metadata-service' => 'v3.3.9@8488d3a832a38cc81c670fce05de1e515c6e64b1',
  'web-auth/webauthn-lib' => 'v3.3.9@04b98ee3d39cb79dad68a7c15c297c085bf66bfe',
  'nextcloud/3rdparty' => 'dev-master@b712fcb86411da2f8547100e28f3e586dee52ead',
);

    private function __construct()
    {
    }

    /**
     * @psalm-pure
     *
     * @psalm-suppress ImpureMethodCall we know that {@see InstalledVersions} interaction does not
     *                                  cause any side effects here.
     */
    public static function rootPackageName() : string
    {
        if (!class_exists(InstalledVersions::class, false) || !InstalledVersions::getRawData()) {
            return self::ROOT_PACKAGE_NAME;
        }

        return InstalledVersions::getRootPackage()['name'];
    }

    /**
     * @throws OutOfBoundsException If a version cannot be located.
     *
     * @psalm-param key-of<self::VERSIONS> $packageName
     * @psalm-pure
     *
     * @psalm-suppress ImpureMethodCall we know that {@see InstalledVersions} interaction does not
     *                                  cause any side effects here.
     */
    public static function getVersion(string $packageName): string
    {
        if (class_exists(InstalledVersions::class, false) && InstalledVersions::getRawData()) {
            return InstalledVersions::getPrettyVersion($packageName)
                . '@' . InstalledVersions::getReference($packageName);
        }

        if (isset(self::VERSIONS[$packageName])) {
            return self::VERSIONS[$packageName];
        }

        throw new OutOfBoundsException(
            'Required package "' . $packageName . '" is not installed: check your ./vendor/composer/installed.json and/or ./composer.lock files'
        );
    }
}
