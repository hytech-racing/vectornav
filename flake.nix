{
    inputs = {
        nixpkgs.url = "nixpkgs/nixos-23.05";
        vn_driver_lib.url = "github:RCMast3r/vn_driver_lib";
        easy_cmake.url = "github:RCMast3r/easy_cmake";
    };

    outputs = { self, nixpkgs, vn_driver_lib, easy_cmake }: 
        let
            vn_driver_overlay = final: prev: rec {
                vn_driver = final.callPackage ./default.nix { 
                    stdenv = final.stdenv;
                    cmake = final.cmake;
                    vn_driver_lib = vn_driver_lib.packages.${final.system}.vn_lib;
                    easy_cmake = final.easy_cmake;
                };
            };

            my_overlays = [ vn_driver_lib.overlays.default vn_driver_overlay easy_cmake.overlays.default ];

            pkgs = import nixpkgs {
                system = "aarch64-darwin";
                overlays = [ self.overlays.default ];
            };
        in
            {
                packages.aarch64-darwin.default = pkgs.vn_driver;
                overlays.default = nixpkgs.lib.composeManyExtensions my_overlays;
            };
}