#include <iostream>
#include <string>
#include <conio.h>
#include <math.h>

using namespace std;

const string abc = "abcdefghijklmnopqrstuvwxyz";

bool IsSimple(int n) {
	bool ret = true;
	if (n == 0 || n == 1) ret = false;
	else {
		for (int i = 2; i <= n / 2; ++i) {
			if (n % i == 0) {
				ret = false;
				break;
			}
		}
	}return ret;
}

string toUpper(string intext) {
	string outtext = "";
	for (int i = 0; i < intext.length(); ++i) {
		outtext += toupper(intext[i]);
	}return outtext;
}

string scaleKey(string text, string key) {
	int i = 0;
	while (key.length() < text.length()) {
		key += key[i];
		if (i < key.length()) i++;
		else i = 0;
	}
	return key;
}

string scaleText(string text, string key) {
	int i = 0;
	while (text.length() % 8 != 0) {
		text += "a";
		if (i < text.length()) i++;
		else i = 0;
	}
	return text;
}

string deleteWhiteSpaces(string str) {
	string newstr = "";
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] != ' ') {
			newstr += str[i];
		}
	}return newstr;
}

int modulo(int a, int b) {
	if (a >= 0)
		return a % b;
	else
		return (b - abs(a % b)) % b;
}
void PrintMatr(int** mas, int m) {
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}
void GetMatr(int** mas, int** p, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
			if (kj == j) dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}
int Determinant(int** mas, int m) {
	int i, j, d, k, n;
	int** p;
	p = new int* [m];
	for (i = 0; i < m; i++)
		p[i] = new int[m];
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	n = m - 1;
	if (m < 1) cout << "Determinant is uncountable!";
	if (m == 1) {
		d = mas[0][0];
		return d;
	}
	if (m == 2) {
		d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
		return d;
	}
	if (m > 2) {
		for (i = 0; i < m; i++) {
			GetMatr(mas, p, i, 0, m);
			d = d + k * mas[i][0] * Determinant(p, n);
			k = -k;
		}
	}
	return d;
}
int Determinant(string mas) {
	int** mkey = new int* [sqrt(mas.length())];
	for (int i = 0; i < sqrt(mas.length()); ++i)
		mkey[i] = new int[sqrt(mas.length())];
	int iterator = 0;
	for (int i = 0; i < sqrt(mas.length()); ++i) {
		for (int j = 0; j < sqrt(mas.length()); ++j) {
			for (int k = 0; k < abc.length(); ++k) {
				if (toupper(mas[iterator]) == toupper(abc[k])) {
					mkey[i][j] = k;
					iterator++;
					break;
				}
			}

		}
	}
	int i, j, d, k, n;
	int** p;
	p = new int* [sqrt(mas.length())];
	for (i = 0; i < sqrt(mas.length()); i++)
		p[i] = new int[sqrt(mas.length())];
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	n = sqrt(mas.length()) - 1;
	if (sqrt(mas.length()) < 1) cout << "Determinant is uncountable!";
	if (sqrt(mas.length()) == 1) {
		d = mkey[0][0];
		return d;
	}
	if (sqrt(mas.length()) == 2) {
		d = mkey[0][0] * mkey[1][1] - (mkey[1][0] * mkey[0][1]);
		return d;
	}
	if (sqrt(mas.length()) > 2) {
		for (i = 0; i < sqrt(mas.length()); i++) {
			GetMatr(mkey, p, i, 0, sqrt(mas.length()));
			d = d + k * mkey[i][0] * Determinant(p, n);
			k = -k;
		}
	}
	return d;
}

int** Algebraic(int** mas, int m) {
	int** alg = new int* [m];
	for (int i = 0; i < m; ++i)
		alg[i] = new int[m];

	alg[0][0] = mas[0][0];
	alg[1][0] = -mas[0][1];
	
	alg[0][1] = -mas[1][0];;
	alg[1][1] = mas[1][1];;
	
	return alg;
}

string encryptVizhener(string text, string key) {
	string e_text;
	for (int i = 0; i < text.length(); ++i)
		e_text += ((text[i] + key[i]) % 26) + 65;
	return e_text;
}

string decryptVizhener(string text, string key) {
	string d_text;
	for (int i = 0; i < text.length(); ++i)
		d_text += modulo(text[i] - key[i], 26) + 65;
	return d_text;
}

string encryptVernam(string text, string key) {
	string e_text;
	for (int i = 0; i < text.length(); ++i) {
		e_text += text[i] ^ key[i];
	}
	return e_text;
}

string decryptVernam(string text, string key) {
	string d_text;
	for (int i = 0; i < text.length(); ++i) {
		d_text += text[i] ^ key[i];
	}
	return d_text;
}

string encryptHill(string text, string key) {
	string e_text = "";
	int* mtext = new int[text.length()];
	int** mkey = new int*[sqrt(key.length())];
	for (int i = 0; i < sqrt(key.length()); ++i) //Ініціалізація двовимірного масиву
		mkey[i] = new int[sqrt(key.length())];
	int iterator = 0;
	for (int i = 0; i < text.length(); ++i) {
		for (int j = 0; j < abc.length(); ++j) {
			if (toupper(text[i]) == toupper(abc[j])) mtext[i] = j; //запис вхідного тексту у вигляді масиву цілих чисел
		}
	}for (int i = 0; i < sqrt(key.length()); ++i) {
		for (int j = 0; j < sqrt(key.length()); ++j) {
			for (int k = 0; k < abc.length(); ++k) {
				if (toupper(key[iterator]) == toupper(abc[k])) { //Запис ключа у вигляді двовимірного масиву цілих чисел
					mkey[i][j] = k;
					iterator++;
					break;
				}
			}
			
		}
	}int* metext = new int[text.length()];
	for (int i = 0; i < text.length(); ++i) //Присвоєння елементам одновимірного масиву значень 0
		metext[i] = 0;
	for (int i = 0; i < text.length(); i+=2) {
		for (int j = 0; j < sqrt(key.length()); ++j) {
			for (int k = 0; k < sqrt(key.length()); ++k)
				metext[i+j] += mtext[i+k] * mkey[k][j]; //
			metext[i+j] = metext[i+j] % 26;
		}
	}for (int i = 0; i < text.length(); ++i) {
		for (int j = 0; j < abc.length(); ++j) {
			if (metext[i] == j) {
				e_text += toupper(abc[j]);
			}
		}
	}return e_text;
}

string decryptHill(string text, string key) {
	string d_text = "";
	int* mtext = new int[text.length()];
	int** mkey = new int* [sqrt(key.length())];
	for (int i = 0; i < sqrt(key.length()); ++i)
		mkey[i] = new int[sqrt(key.length())];
	int iterator = 0;
	for (int i = 0; i < text.length(); ++i) {
		for (int j = 0; j < abc.length(); ++j) {
			if (toupper(text[i]) == toupper(abc[j])) {
				mtext[i] = j;
			}
		}
	}
	for (int i = 0; i < sqrt(key.length()); ++i) {
		for (int j = 0; j < sqrt(key.length()); ++j) {
			for (int k = 0; k < abc.length(); ++k) {
				if (toupper(key[iterator]) == toupper(abc[k])) {
					mkey[i][j] = k;
					iterator++;
					break;
				}
			}

		}
	}
	int** invmkey = new int* [sqrt(key.length())];
	for (int i = 0; i < sqrt(key.length()); ++i)
		invmkey[i] = new int[sqrt(key.length())];

	for (int i = 0; i < sqrt(key.length()); ++i) {
		for (int j = 0; j < sqrt(key.length()); ++j) {
			invmkey[j][i] = (1 / Determinant(mkey, sqrt(key.length()))) * Algebraic(mkey, sqrt(key.length()))[i][j];
		}
	}
	int* metext = new int[text.length()];
	for (int i = 0; i < text.length(); ++i)
		metext[i] = 0;
	for (int i = 0; i < text.length(); i += 2) {
		for (int j = 0; j < sqrt(key.length()); ++j) {
			for (int k = 0; k < sqrt(key.length()); ++k) {
				metext[i + j] += mtext[i + k] * invmkey[k][j];
			}
			metext[i + j] % 26 < 0 ? metext[i + j] = (metext[i + j] % 26)+26 : metext[i + j] = metext[i + j] % 26;
		}
	}
	for (int i = 0; i < text.length(); ++i) {
		for (int j = 0; j < abc.length(); ++j) {
			if (metext[i] == j) {
				d_text += toupper(abc[j]);
			}
		}
	}
	return d_text;
}

string encryptGronsfeld(string text, string key) {
	string e_text="";
	int nd = 0;
	int* digits = new int[key.length()];
	int* mtext = new int[text.length()];
	for (int i = 0; i < key.length(); ++i) {
		if (isdigit(key[i])) {
			nd++;
			digits[i] = key[i]%48;
		}
	}if (nd == key.length()) {
		for (int i = 0; i < text.length(); ++i) {
			for (int j = 0; j < abc.length(); ++j) {
				if (toupper(text[i]) == toupper(abc[j])) {
					mtext[i] = j;
				}
			}
		}
		for (int i = 0; i < text.length(); ++i) {
			e_text += toupper(abc[(mtext[i]+digits[i])%26]);
		}
		return e_text;
	}return "error";
}

string decryptGronsfeld(string text, string key) {
	string d_text = "";
	int nd = 0;
	int* digits = new int[key.length()];
	int* mtext = new int[text.length()];
	for (int i = 0; i < key.length(); ++i) {
		if (isdigit(key[i])) {
			nd++;
			digits[i] = key[i] % 48;
		}
	}if (nd == key.length()) {
		for (int i = 0; i < text.length(); ++i) {
			for (int j = 0; j < abc.length(); ++j) {
				if (toupper(text[i]) == toupper(abc[j])) {
					mtext[i] = j;
				}
			}
		}
		for (int i = 0; i < text.length(); ++i) {
			d_text += toupper(abc[(abs(mtext[i] - digits[i])) % 26]);
		}
		return d_text;
	}return "error";
}

int64_t* textToCode(string text) {
	int64_t* code = new int64_t[text.length()];
	for (int i = 0; i < text.length(); i++) {
		for (int j = 0; j < abc.length(); j++) {
			if (toupper(text[i]) == toupper(abc[j])) {
				code[i] = j;
			}
		}
		
	}return code;
}

string codeToText(int64_t* code, int length) {
	string text = "";
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < abc.length(); j++) {
			if (code[i] == j) {
				text += toupper(abc[j]);
			}
		}

	}return text;
}

int64_t Eiler(int64_t s1, int64_t s2) {
	return (s1 - 1) * (s2 - 1);
}

int64_t PrivateKeyValue(int64_t e, int64_t phi) {
	int64_t d = 0;
	while ((d * e) % phi != 1) {
		d++;
	}return d;
}

int64_t encryptRSA(int64_t c, int64_t e, int64_t n, int64_t r) {
	int64_t m = 0;
	for (int64_t i = 0; i < e; i++) {
		m = (r * c);
		r = m % n;
	}return r;
	/*int ret = pow(c, e);
	ret = ret % n;
	return ret;*/
}

int64_t decryptRSA(int64_t c, int64_t d, int64_t n, int64_t r) {
	int64_t m = 0;
	for (int64_t i = 0; i < d; i++) {
		m = (r * c);
		r = m % n;
	}return r;
	/*int ret = pow(c, d);
	ret = ret % n;
	return ret;*/
}

int main()
{
	srand(time(0));
	int menu = 1;
	int mode = 1;

	string text = "";
	string* textHill;
	int64_t* textRSA = 0;
	int64_t* tmp = 0;
	string key = "";
	int64_t publicKey = 0;
	int64_t privateKey = 0;
	int64_t simple1 = 0;
	int64_t simple2 = 0;
	string randkey = "";
	bool randflag = false;
	string decrypted = "";
	string encrypted = "";
	int64_t* decryptedRSA;
	int64_t* encryptedRSA;
	int index = 0;

	while (menu != 48)
	{
		//system("cls");
		cout << "===Course work===\n";
		cout << "1. Vizhener\n";
		cout << "2. Vernam\n";
		cout << "3. Hill\n";
		cout << "4. Gronsfeld\n";
		cout << "5. RSA\n";
		cout << "0. Terminate application\n";
		cout << "=================\n";

		menu = _getch();
		switch (menu)
		{
		case 49:
			cout << "Encrypt(1) or decrypt(2)? _\b";
			mode = _getch();
			switch (mode)
			{
			case 49:
				cout << "\nEnter text to encrypt => _\b";
				getline(cin, text);
				text = deleteWhiteSpaces(text);
				cout << "Enter key (must be only letters and count must be less or equal "<< text.length() << ") => _\b";
				cin >> key;
				while (key.length() > text.length()) {
					cout << "\nWrong key! It must be only letters and count must be less or equal " << text.length() << " => _\b";
					cin >> key;
				}
				key = scaleKey(text, key);
				text = toUpper(text);
				key = toUpper(key);
				encrypted = encryptVizhener(text, key);
				cout << "Text - " << text << endl;
				cout << "Encrypted - " << encrypted << endl;
				break;
			case 50:
				cout << "\nEnter text to decrypt => _\b";
				cin >> text;
				cout << "Enter key (must be only letters and count must be less or equal " << text.length() << ") => _\b";
				cin >> key;
				while (key.length() > text.length()) {
					cout << "\nWrong key! It must be only letters and count must be less or equal " << text.length() << " => _\b";
					cin >> key;
				}
				key = scaleKey(text, key);
				text = toUpper(text);
				key = toUpper(key);
				decrypted = decryptVizhener(text, key);
				cout << "Text - " << text << endl;
				cout << "Decrypted - " << decrypted << endl;

				break;
			default:
				break;
			}
			break;
		case 50:
			cout << "Encrypt(1) or decrypt(2)? _\b";
			mode = _getch();
			switch (mode)
			{
			case 49:
				cout << "\nEnter text to encrypt => _\b";
				getline(cin, text);
				text = toUpper(text);
				text = deleteWhiteSpaces(text);
				if (!randflag) {
					for (int i = 0; i < text.length(); ++i)
						randkey += (char)((rand() % 26) + 97);
					randflag = true;
				}
				encrypted = encryptVernam(text, randkey);
				cout << "Text - " << text << endl;
				cout << "Random key - " << randkey << endl;
				cout << "Encrypted - " << encrypted << endl;
				break;
			case 50:
				cout << "\nEnter text to decrypt => _\b";
				getline(cin, text);
				if (!randflag) {
					for (int i = 0; i < text.length(); ++i)
						randkey += (char)((rand() % 26) + 97);
					randflag = true;
				}
				decrypted = decryptVernam(text, randkey);
				cout << "Text - " << text << endl;
				cout << "Random key - " << randkey << endl;
				cout << "Decrypted - " << decrypted << endl;
				break;
			default:
				break;
			}
			break;
		case 51:
			cout << "Encrypt(1) or decrypt(2)? _\b";
			mode = _getch();
			switch (mode)
			{
			case 49:
				cout << "\nEnter text to encrypt => _\b";
				getline(cin, text);
				text = deleteWhiteSpaces(text);
				cout << "Enter key (letters count must be equal 4 and determinant must be equal 1) = > _\b";
				cin >> key;
				while (key.length() != 4 || Determinant(key) != 1) {
					cout << "Wrong! Letters count must be equal 4 and determinant must be equal 1!\nEnter key => _\b";
					cin >> key;
				}
				text = scaleText(text, key);
				text = toUpper(text);
				key = toUpper(key);
				textHill = new string[text.length()/8];
				for (int i = 0; i < text.length() / 8; ++i) {
					for (int j = i*8; j < 8*(i+1); ++j) {
						textHill[i] += text[j];
					}

				}
				for (int i = 0; i < ceil(text.length() / (double)8); ++i) {
					encrypted += encryptHill(textHill[i], key);
				}
				cout << "Text - " << text << endl;
				cout << "Encrypted - " << encrypted << endl;
				break;
			case 50:
				cout << "\nEnter text to decrypt => _\b";
				cin >> text;
				cout << "Enter key (letters count must be equal 4 and determinant must be equal 1) = > _\b";
				cin >> key;
				while (key.length() != 4 && Determinant(key)!=1) {
					cout << "Wrong! Letters count must be equal 4 and determinant must be equal 1!\nEnter key => _\b";
					cin >> key;
				}
				
				text = toUpper(text);
				key = toUpper(key);

				decrypted = decryptHill(text, key);
				cout << "Text - " << text << endl;
				cout << "Decrypted - " << decrypted << endl;
				break;

			default:
				break;
			}
			break;
		case 52:
			cout << "Encrypt(1) or decrypt(2)? _\b";
			mode = _getch();
			switch (mode)
			{
			case 49:
				cout << "\nEnter text to encrypt => _\b";
				getline(cin, text);
				text = deleteWhiteSpaces(text);
				cout << "Enter key (only digits and less or equal "<< text.length() << ") = > _\b";
				cin >> key;
				while (key.length() > text.length()) {
					cout << "\nWrong key! It must be only digits and count must be less or equal " << text.length() << " => _\b";
					cin >> key;
				}
				key = scaleKey(text, key);
				text = toUpper(text);

				encrypted = encryptGronsfeld(text, key);
				cout << "Text - " << text << endl;
				cout << "Encrypted - " << encrypted << endl;
				break;
			case 50:
				cout << "\nEnter text to decrypt => _\b";
				cin >> text;
				cout << "Enter key (only digits and less or equal " << text.length() << ") = > _\b";
				cin >> key;
				while (key.length() > text.length()) {
					cout << "\nWrong key! It must be only digits and count must be less or equal " << text.length() << " => _\b";
					cin >> key;
				}
				key = scaleKey(text, key);
				text = toUpper(text);

				decrypted = decryptGronsfeld(text, key);
				cout << "Text - " << text << endl;
				cout << "Decrypted - " << decrypted << endl;
				break;
			default:
				break;
			}
		break;
		case 53:
			cout << "Encrypt(1) or decrypt(2)? _\b";
			mode = _getch();
			switch (mode)
			{
			case 49:
				cout << "\nEnter text to encrypt => _\b";
				getline(cin, text);
				text = deleteWhiteSpaces(text);
				cout << "Enter first random simple number => _\b";
				cin >> simple1;
				while (!IsSimple(simple1)) {
					cout << "\nWrong! It must be only simple! => _\b";
					cin >> simple1;
				}
				cout << "Enter second random simple number => _\b";
				cin >> simple2;
				while (!IsSimple(simple2)) {
					cout << "\nWrong! It must be only simple! => _\b";
					cin >> simple2;
				}

				cout << "Enter public key (must be simple, less and coprime to number \""<<Eiler(simple1, simple2) << "\" and less than it) => _\b";
				cin >> publicKey;

				encryptedRSA = new int64_t[text.length()];

				for (int i = 0; i < text.length(); ++i) {
					encryptedRSA[i] = encryptRSA(textToCode(text)[i], publicKey, simple1 * simple2, (int64_t)1);
				}
				encrypted = codeToText(encryptedRSA, text.length());
				cout << "Text - " << text << endl;
				cout << "Encrypted: ";
				for (int i = 0; i < text.length(); ++i) {
					cout << encryptedRSA[i] << " ";
				}cout << endl;
				break;
			case 50:
				textRSA = new int64_t[index];
				cout << "\nPress any button to start enter massive of numbers to decrypt or press \"S\" button to stop => _\b";
				while(_getch() != 115){
					cout << "Enter value => _\b";
					tmp = textRSA;
					textRSA = new int64_t[++index];
					for (int64_t i = 0; i < index-1; ++i) {
						textRSA[i] = tmp[i];
					}
					cin >> textRSA[index-1];
				}
				

				cout << "Enter first random simple number => _\b";
				cin >> simple1;
				while (!IsSimple(simple1)) {
					cout << "\nWrong! It must be only simple! => _\b";
					cin >> simple1;
				}
				cout << "Enter second random simple number => _\b";
				cin >> simple2;
				while (!IsSimple(simple2)) {
					cout << "\nWrong! It must be only simple! => _\b";
					cin >> simple2;
				}

				cout << "Enter public key (must be simple, less and coprime to number \"" << Eiler(simple1, simple2) << "\" and less than it) => _\b";
				cin >> publicKey;

				decryptedRSA = new int64_t[index];

				for (int i = 0; i < index; ++i) {
					decryptedRSA[i] = decryptRSA(textRSA[i], PrivateKeyValue(publicKey, Eiler(simple1, simple1)), simple1 * simple2, (int64_t)1);
				}
				decrypted = codeToText(decryptedRSA, index);
				cout << "Text - ";
				for (int64_t i = 0; i < index; ++i) {
					cout << textRSA[i] << endl;
				}
				cout << "Decrypted - " << decrypted << endl;
				break;
			default:
				break;
			}
			break;
		case 48:
			cout << "Enter some button to continue... \b";
			_getch();
			text = "";
			key = "";
			index = 0;
			publicKey = 0;
			privateKey = 0;
			decrypted = "";
			encrypted = "";
		default:
			break;
			cout << "Enter some button to continue... \b";
			_getch();
			text = "";
			key = "";
			index = 0;
			publicKey = 0;
			privateKey = 0;
			decrypted = "";
			encrypted = "";
		}
	}
	return 0;
}