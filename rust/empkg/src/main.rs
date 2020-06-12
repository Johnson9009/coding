use std::{env, fs};
use yaml_rust::YamlLoader;

fn main() {
  let pkg_path = env::args()
                 .nth(1)
                 .expect("The path of emacs package directory must be given.");

  let excludes = vec![String::from("archives")];
  let mut packages = Vec::new();
  for entry in fs::read_dir(pkg_path).unwrap() {
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

  let pkg_file = env::args()
                 .nth(2)
                 .expect("The path of emacs package describe file must be set.");
  let yaml_string = fs::read_to_string(pkg_file).unwrap();
  let docs = YamlLoader::load_from_str(&yaml_string).unwrap();
  let doc = &docs[0];

  println!("{:?}", doc);
}
