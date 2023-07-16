#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/// \brief ImportText import the text for encryption
/// \param inputFilePath: the input file path
/// \param text: the resulting text
/// \return the result of the operation, true is success, false is error
bool ImportText(const string& inputFilePath,
                string& text);

/// \brief Encrypt encrypt the text
/// \param text: the text to encrypt
/// \param password: the password for encryption
/// \param encryptedText: the resulting encrypted text
/// \return the result of the operation, true is success, false is error
bool Encrypt(const string& text,
             const string& password,
             string& encryptedText);

/// \brief Decrypt decrypt the text
/// \param text: the text to decrypt
/// \param password: the password for decryption
/// \param decryptedText: the resulting decrypted text
/// \return the result of the operation, true is success, false is error
bool Decrypt(const string& text,
             const string& password,
             string& decryptedText);

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cerr<< "Password shall passed to the program"<< endl;
    return -1;
  }
  string password = argv[1];

  string inputFileName = "./text.txt", text;
  if (!ImportText(inputFileName, text))
  {
    cerr<< "Something goes wrong with import"<< endl;
    return -1;
  }
  else
    cout<< "Import successful: result= "<< text<< endl;

  string encryptedText;
  if (!Encrypt(text, password, encryptedText))
  {
    cerr<< "Something goes wrong with encryption"<< endl;
    return -1;
  }
  else
    cout<< "Encryption successful: result= "<< encryptedText<< endl;

  string decryptedText;
  if (!Decrypt(encryptedText, password, decryptedText) || text != decryptedText)
  {
    cerr<< "Something goes wrong with decryption"<< endl;
    return -1;
  }
  else
    cout<< "Decryption successful: result= "<< decryptedText<< endl;

  return 0;
}

bool ImportText(const string& inputFilePath,
                string& text)
{
  ifstream inputFile(inputFilePath);
  if(inputFile.is_open()){
    return false;
  }
  stringstream buffer;
  buffer<<inputFile.rdbuf();
  text=buffer.str();

  inputFile.close();
  return true;
}

bool Encrypt(const string& text,
             const string& password,
             string& encryptedText)
{
  if (text.empty() || password.empty()) {
    return false;  // Non è possibile cifrare il testo vuoto o una password vuota
  }
  // normalizziamo la password per adattarla alla lunghezza del testo.
  string normalizedPassword;
  size_t passwordLenght=password.length();
  for(size_t i=0; i<text.length();i++)
  {
    char currentChar=password[i % passwordLenght];
    normalizedPassword+=currentChar;
  }
  //cifriamo carattere per carattere
  for (size_t i = 0; i < text.length(); i++)
  {
    char currentChar = text[i];
    char passwordChar = normalizedPassword[i];
    char encryptedChar = (currentChar + passwordChar) % 26 + 'A';  // Applica la regola di cifratura di Vigenère
    encryptedText += encryptedChar;
  }
  return true;
}

bool Decrypt(const string& text,
             const string& password,
             string& decryptedText)
{
  if (text.empty() || password.empty()) {
    return false;  // Non è possibile cifrare il testo vuoto o una password vuota
  }

  // Normalizza la password per adattarla alla lunghezza del testo cifrato
  string normalizedPassword;
  size_t passwordLength = password.length();
  for (size_t i = 0; i < text.length(); i++) {
    char currentChar = password[i % passwordLength];
    normalizedPassword += currentChar;
  }

  // Decrittazione del testo cifrato
  for (size_t i = 0; i < text.length(); i++) {
    char encryptedChar = text[i];
    char passwordChar = normalizedPassword[i];
    char decryptedChar = (encryptedChar - passwordChar + 26) % 26 + 'A';  // Applica la regola di decrittazione di Vigenère
    decryptedText += decryptedChar;
  }

  return true;
}
