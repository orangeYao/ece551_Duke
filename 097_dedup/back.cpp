
int main2()
{
  string file = "/var/dedup/d001/bcbbbcabb";
  string file2 = "/var/dedup/d000/file444";
  cout << reading(file); 
  cout << hashing(reading(file)) << endl;
  cout << reading(file2); 
  cout << hashing(reading(file2)) << endl;
  return 0;
}
