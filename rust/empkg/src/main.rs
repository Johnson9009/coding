
fn main() -> std::io::Result<()> {
  for entry in std::fs::read_dir("/Users/johnson/.emacs.d/elpa/25.3/develop")? {
    let entry = entry?;
    if entry.file_type()?.is_dir() == true {
      println!("dir: {:?}", entry.file_name());
    }
  }
  Ok(())
}
