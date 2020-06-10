
fn main() {
  let pkg_path = std::env::args()
                 .nth(1)
                 .expect("The path of emacs package directory must be given.");

  let excludes = vec![String::from("archives")];
  let mut packages = Vec::new();
  for entry in std::fs::read_dir(pkg_path).unwrap() {
    let entry = entry.unwrap();
    if entry.file_type().unwrap().is_dir() == true {
      let dir_name = entry.file_name().into_string().unwrap();
      if excludes.contains(&dir_name) {
        continue;
      }
      packages.push(dir_name.rsplitn(2, '-').last().unwrap().to_owned());
    }
  }
  println!("packages: {:#?}", packages);
}
