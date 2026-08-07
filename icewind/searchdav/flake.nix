{
  inputs = {
    nixpkgs.url = "nixpkgs/release-26.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    utils,
  }:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
      };
      phpPackages = pkgs.php82Packages;
      phpPackage = pkgs.php82.buildEnv {
        extensions = {
          enabled,
          all,
        }:
          enabled
          ++ (with all; [
            xmlwriter
          ]);
      };
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = [
          phpPackage
          phpPackages.composer
          (phpPackages.box.override {php82 = phpPackage;})
        ];
      };
    });
}
