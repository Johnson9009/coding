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
  let known_packages = docs[0].as_vec().unwrap()
                       .iter()
                       .map(|x| x.as_str().unwrap().to_owned())
                       .collect::<Vec<String>>();
  println!("unknown packages: {:?}", packages.iter().filter(|x| known_packages.contains(x) == false).collect::<Vec<_>>());
  println!("Removed known packages: {:?}", known_packages.iter().filter(|x| packages.contains(x) == false).collect::<Vec<_>>());
}
