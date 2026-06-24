use cxx::CxxString;
use cxx::UniquePtr;
use std::pin::Pin;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ransac_bridge/include/ransac_bridge.h");
        type Table;

        fn table_from_csv(path: &CxxString) -> UniquePtr<Table>;

        fn run_ransac(table: Pin<&mut Table>, threshold: f64) -> f64;
    }
}

pub use ffi::{table_from_csv, run_ransac, Table};

