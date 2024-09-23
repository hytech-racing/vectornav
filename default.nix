{ stdenv, cmake, vn_driver_lib, easy_cmake }:
stdenv.mkDerivation {
    pname = "vn_driver";
    version = "0.0.1";
    src = ./.;
    nativeBuildInputs = [ cmake  vn_driver_lib easy_cmake ];
}