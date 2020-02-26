#include <ontiolib/ontio.hpp>
#include <regex>

using namespace ontio;
using std::string;
using std::regex;

class hello: public contract {
		string filetext = R"(a[bcd]+ef.[^gh]?ijk$,abcdefgijk,TRUE
Ontology,Ontology is the best,TRUE
\\,a,FALSE
\\,\,TRUE
.,,FALSE
[abc.],d.d,TRUE
[.],abc.,TRUE
a[bc]d,dddacdd,TRUE
a[bc]d,cdd,FALSE
a[bc],aaaaaaaab,TRUE
a[b]d[d],abcdabcd,FALSE
^abc,ababcddd,FALSE
^abc,abcdd,TRUE
^a?bc,bcddabcdabcdabcdabcd,TRUE
^a?bc,abcdd,TRUE
^a?bc,aabcdddd,FALSE
aaa$,aaa,TRUE
a+$,a,TRUE
a+$,abaa,TRUE
a+$,abcd,FALSE
[abc]?def,adef,TRUE
[abc]?def,def,TRUE
[abc]?def,aadef,TRUE
[abc]?def,aaaaadef,TRUE
[abc]?def,afed,FALSE
[abc]?def,defddd,TRUE
a[abc]?def,adef,TRUE
a[abc]?def,abcdef,FALSE
a[abc]?def,aaacdef,TRUE
[abc]*def,def,TRUE
[abc]*def,adef,TRUE
[abc]*def,abcdef,TRUE
[abc]*def,aadef,TRUE
[abc]*def,aaaadef,TRUE
[abc]*def,adefddd,TRUE
[abc]*def,defdddd,TRUE
a[abc]*def,adef,TRUE
a[abc]*def,aabdef,TRUE
a[abc]*def,aaacdef,TRUE
a[abc]*def,abcddef,FALSE
[abc]+def,def,FALSE
[abc]+def,aadef,TRUE
[abc]+def,aaaadef,TRUE
[abc]+def,adef,TRUE
[abc]+def,defdddd,FALSE
a[abc]+def,adef,FALSE
a[abc]+def,abcdef,TRUE
a[abc]+def,aabcdef,TRUE
^a,bac,FALSE
a$,abc,FALSE
^$,,TRUE
^[^abc]?def,def,TRUE
^[^abc]*def,def,TRUE
^[^abc]*def,xdef,TRUE
^[^abc]*def,xxdef,TRUE
^[^abc]+def,def,FALSE
^[^abc]+def,xdef,TRUE
^[^abc]+def,xxdef,TRUE
a,bbbbbbbbbbbbbbbbbbbbbbb,FALSE
abc,abcddddddddddddddddddd,TRUE
aaa,aabaabaabaabaabaabaaadd,TRUE
.,abcddddddddddddddddddd,TRUE
[a],bbbabcdddddddddddddddd,TRUE
[abc],bdddddddddddddddddd,TRUE
[abc],dddddddddddddddddd,FALSE
[ab]cd,aaaaaaaaaaabbbbbbbbbcd,TRUE
[ab]cd,bcddddddddddddddddddd,TRUE
[ab]cd,aaaaabbbbbxccccccdddddd,FALSE
a[bc]d,dddabcddabcdabcdabcdabc,FALSE
aaa$,aaaaaaaaaaaaaaaaaaaaabaa,FALSE
[abc]?def,aaaabbbbbbbddddddfabcdef,TRUE
[abc]?def,abcdeabcdeabcedabcdeabcdef,TRUE
[abc]?def,fffeeeaaaaaccccccddeeadefdd,TRUE
[abc]?def,effffffeeccsssseeeeeabcde,FALSE
a[abc]?def,abbbdeeffffedefdefaaabdef,TRUE
a[abc]?def,ccccddddeeeffffaabcdef,FALSE
[abc]*def,aaaaacccccddddabcde,FALSE
[abc]*def,abcdeabcdeabcdef,TRUE
[abc]*def,aaaaacccccdddddafed,FALSE
a[abc]*def,fffffeeeeecccddddabcdef,TRUE
a[abc]*def,xxxeeeeffffdefaaabbaabcdef,TRUE
[abc]+def,aaaaabbbbbbccccccadef,TRUE
[abc]+def,abcdeffffaaacceeff,TRUE
[abc]+def,abcdeddddeffffeeee,FALSE
[abc]+def,abcdeabcdeabcdef,TRUE
[abc]+def,feeeeecccddddadefddd,TRUE
a[abc]+def,aaccccddddefffffabdef,TRUE
a[abc]+def,ffeeeeecccddddddaaacdef,TRUE
^a,abcddddddddddddddddddd,TRUE
a$,cbadddddddddddddddddda,TRUE
^$,aabbbccccdddddeeeeeefffffff,FALSE
^[^abc]?def,xdefaaaabbbbbccccdddef,TRUE
^[^abc]?def,xxdefaaabbbbbccccdddef,FALSE
[abcde]*a+b?,a,TRUE
[abcde]*a+b?,ab,TRUE
[abcde]*a+b?,abc,TRUE
[abcde]*a+b?,abcd,TRUE
[abcde]*a+b?,abcde,TRUE
[abcde]*a+b?,abcdef,TRUE
[abcde]*a+b?,bcdefa,TRUE
[abcde]*a+b?,bcdefg,FALSE
[abcde]+a*b?,a,TRUE
[abcde]+a*b?,ab,TRUE
[abcde]+a*b?,abc,TRUE
[abcde]+a*b?,abcd,TRUE
[abcde]+a*b?,abcde,TRUE
[abcde]+a*b?,abcdef,TRUE
[abcde]+a*b?,bhijklmn,TRUE
[abcde]+a*b?,zzzzzzzzz,FALSE
[abcde]?a*b+,a,FALSE
[abcde]?a*b+,ab,TRUE
[abcde]?a*b+,abc,TRUE
[abcde]?a*b+,abcd,TRUE
[abcde]?a*b+,abcde,TRUE
[abcde]?a*b+,bhijklmn,TRUE
[abcde]?a*b+,zzzzzzzzz,FALSE
[ab]?[cd].e.f+g$,cxeyfg,TRUE
[ab]?[cd].e.f+g$,aaaaaacxeydfg,FALSE
[ab]?[cd].e.f+g$,aaaabbbbcceeffg,TRUE
[ab]?[cd].e.f+g$,cceefffffffffffg,TRUE
[ab]?[cd].e.f+g,cceeffhhgg,FALSE
[ab]?[cd].e.f+g,dxeyffffffg,TRUE
[ab]?[cd].e.f+g$,bbbbaaaadxeyffg,TRUE
[ab]?[cd].e.f+g$,ababababcdcdcdcdexg,FALSE
[ab]?[cd].e.f+g$,abcdefghijk,FALSE
[ab]?[cd].e.f+g$,*ac?e.fg,TRUE
[ab]?[cd].e.f+g,01234567abcdeeffgghhii,TRUE
[ab]?[cd].e.f+g,cdeefg01234567890cdeefg,TRUE
a?[^ab]+ac*d,cad,TRUE
a?[^ab]+ac*d,acad,TRUE
a?[^ab]+ac*d,abcad,TRUE
a?[^ab]+ac*d,abcacd,TRUE
a?[^ab]+ac*d,abcdabcaccd,TRUE
ba?[^ab]+ac*d,abcdabcaccd,TRUE
ba?[^ab]+ac*d,abcdcbacad,TRUE
ba?[^ab]+ac*d,abababacd,FALSE
ba?[^ab]+ac*d,ababacabcacd,TRUE
ba?[^ab]+ac*d,abcabcabcabd,FALSE
a+b+c+d+e+f,abcdef,TRUE
a+b+c+d+e+f,0a2b3c4d5e6f,FALSE
a+b+c+d+e+f,aabbbccccdddddeeeeeefffffff,TRUE
a+b+c+d+e+f,abcdeabcdefabcdeabcdef,TRUE
a+b+c+d+e+f,aabbccddeaabbccddeef,TRUE
a?b+c?d+e?f+,bdf,TRUE
a?b+c?d+e?f+,abcdef,TRUE
a?b+c?d+e?f+,aabbccddeeff,FALSE
a?b+c?d+e?f+,aabbddeff,TRUE
a?b+c?d+e?f+,abcdebbcddff,TRUE
a[bc]?[^de]+e+,ace,TRUE
a[bc]?[^de]+e+,abcef,TRUE
a[bc]?[^de]+e+,aabbcceef,TRUE
a[bc]?[^de]+e+,abcdeabcef,TRUE
a[bc]?[^de]+e+,abcdefabcdef,FALSE
a+[^a]+a+[^a]+a,ababa,TRUE
a+[^a]+a+[^a]+a,abcdabcdabcdabcdabcd,TRUE
a+[^a]+a+[^a]+a,ccaabbccddeeaabbccdd,FALSE
a+[^a]+a+[^a]+a,aabbccaabbccdd,FALSE
a+[^a]+a+[^a]+a,aaa,FALSE
ab+[^a]+ab+[^b]+,abbabba,TRUE
ab+[^a]+ab+[^b]+,aaabbbcccaaabbbccc,FALSE
ab+[^a]+ab+[^b]+,ababababab,FALSE
ab+[^a]+ab+[^b]+,abbaccadd,FALSE
ab+[^a]+ab+[^b]+,abcabcabc,TRUE
a[.*?\]+=/]+b,a.b,TRUE
a[.*?\]+=/]+b,0123a*b,TRUE
a[.*?\]+=/]+b,0123a]b,TRUE
a[.*?\]+=/]+b,0123a]***b,TRUE
a[.*?\]+=/]+b,0123a...cb,FALSE
a[.*?\]+=/]+b,0123a+b,TRUE
a[.*?\]+=/]+b,0123a/b,TRUE
a[.*?\]+=/]+b,0123a=b,TRUE
a[.*?\]+=/]+b,0123a]b,TRUE
a[.*?\]+=/]+b,0123a+=/]b,TRUE
\.[01234]+\.,.1.,TRUE
\.[01234]+\.,123.abc.123,FALSE
\.[01234]+\.,123.123.x,TRUE
\.[01234]+\.,123.123.123.123,TRUE
\.[01234]+\.,abc.123.123,TRUE
^[123]+\.[^ab]+$,1.f,TRUE
^[123]+\.[^ab]+$,3.3,TRUE
^[123]+\.[^ab]+$,1.7.9,TRUE
^[123]+\.[^ab]+$,1.c,TRUE
^[123]+\.[^ab]+$,.d,FALSE
^[123]+\.[^ab]+$,1.df,TRUE
ab?[^a]?ab*[^b]+,0123aac,TRUE
ab?[^a]?ab*[^b]+,abcabc,TRUE
ab?[^a]?ab*[^b]+,abcbabc,FALSE
ab?[^a]?ab*[^b]+,abcdabcd,FALSE
ab?[^a]?ab*[^b]+,cccaaddddff,TRUE
ab?[^a]?ab*[^b]+,abcdeeefsaa,FALSE
ab?[^a]?ab*[^b]+,abcdeeefsaax,TRUE
.b?[^a]?ab*[^b]+,abccdefdsffeaf,TRUE
.b?[^a]?ab*[^b]+,aawiejfijsiidjfllek,TRUE
.b?[^a]?ab*[^b]+,acdijfeijisoica,FALSE
.b?[^a]?ab*[^b]+,xab,FALSE
\.\.\.\.\.,abc,FALSE
\.\.\.x\.\.,a...x..b,TRUE
\.\.\..\.\.,a...*..b,TRUE
\..*\.,a.........b,TRUE
\.\.\.\.\.,....,FALSE
a,a,TRUE
a,b,FALSE
\\,a,FALSE
\\,\,TRUE
abc,abcdd,TRUE
aaa,aabaaadd,TRUE
.,a,TRUE
.,,FALSE
.,abc,TRUE
[a],a,TRUE
[a],abcdddd,TRUE
[a],bcd,FALSE
[abc],b,TRUE
[abc],bdd,TRUE
[abc],d,FALSE
[abc],dd,FALSE
[abc.],d.d,TRUE
[.],abc.,TRUE
[.],abc,FALSE
[ab]cd,acd,TRUE
[ab]cd,bcd,TRUE
[ab]cd,ccd,FALSE
a[bc]d,acd,TRUE
a[bc]d,dddab,FALSE
a[bc]d,dddacdd,TRUE
a[bc]d,cdd,FALSE
a[bc],aaaaaaaab,TRUE
a[b]d[d],abcd,FALSE
^abc,ababcddd,FALSE
^abc,abcdd,TRUE
^a?bc,bcdd,TRUE
^a?bc,abcdd,TRUE
^a?bc,aabcdddd,FALSE
aaa$,aaa,TRUE
a+$,a,TRUE
a+$,abaa,TRUE
a+$,abcd,FALSE
[abc]?def,adef,TRUE
[abc]?def,def,TRUE
[abc]?def,abcdef,TRUE
[abc]?def,aadef,TRUE
[abc]?def,abcde,FALSE
[abc]?def,aaaaadef,TRUE
[abc]?def,abcdeabcdef,TRUE
[abc]?def,afed,FALSE
[abc]?def,adefdd,TRUE
[abc]?def,defddd,TRUE
a[abc]?def,adef,TRUE
a[abc]?def,aabdef,TRUE
a[abc]?def,abcdef,FALSE
a[abc]?def,aaacdef,TRUE
a[abc]?def,aabcdef,FALSE
[abc]*def,def,TRUE
[abc]*def,adef,TRUE
[abc]*def,abcdef,TRUE
[abc]*def,aadef,TRUE
[abc]*def,abcde,FALSE
[abc]*def,aaaadef,TRUE
[abc]*def,abcdeabcdeabcdef,TRUE
[abc]*def,afed,FALSE
[abc]*def,adefddd,TRUE
[abc]*def,defdddd,TRUE
a[abc]*def,adef,TRUE
a[abc]*def,aabdef,TRUE
a[abc]*def,abcdef,TRUE
a[abc]*def,aaacdef,TRUE
a[abc]*def,aabcdef,TRUE
a[abc]*def,abcddef,FALSE
[abc]+def,def,FALSE
[abc]+def,adef,TRUE
[abc]+def,abcdef,TRUE
[abc]+def,aadef,TRUE
[abc]+def,abcde,FALSE
[abc]+def,aaaadef,TRUE
[abc]+def,abcdeabcdeabcdef,TRUE
[abc]+def,adef,TRUE
[abc]+def,adefddd,TRUE
[abc]+def,defdddd,FALSE
a[abc]+def,adef,FALSE
a[abc]+def,aabdef,TRUE
a[abc]+def,abcdef,TRUE
a[abc]+def,aaacdef,TRUE
a[abc]+def,aabcdef,TRUE
^a,abc,TRUE
^a,bac,FALSE
a$,cba,TRUE
a$,abc,FALSE
^$,,TRUE
^$,a,FALSE
^[^abc]?def,def,TRUE
^[^abc]?def,xdef,TRUE
^[^abc]?def,xxdef,FALSE
^[^abc]*def,def,TRUE
^[^abc]*def,xdef,TRUE
^[^abc]*def,xxdef,TRUE
^[^abc]+def,def,FALSE
^[^abc]+def,xdef,TRUE
^[^abc]+def,xxdef,TRUE
a[bcd]+ef.[^gh]?ijk$,abcdefgijk,TRUE)";

		vector<string> split(const std::string &str, char c) {
			vector<string> res;
			uint32_t len_t = str.size();
			uint32_t i = 0;
			string t("");

			for(i = 0; i < len_t; i++) {
				char x = str[i];
				if (x == ' ') {
					continue;
				} else if (x != c) {
					t.push_back(x);
				} else {
					if (t != "") {
						res.push_back(t);
					} else {
						res.push_back("");
					}
					t = "";
				}
			}

			res.push_back(t);
			return res;
		}

		bool test_regex_match(string &text, string &pattern) {
			//printf("%s, %s\n", text.c_str(), pattern.c_str());
			regex re(pattern);
			if (std::regex_search(text, re))
				return true;
			else
				return false;
		}

	public:
		using contract::contract;
		bool performance_test(uint32_t count) {
			check(filetext.size() != 0, "filetext size zero\n");
			auto filetextarray = split(filetext,'\n');
			check(filetextarray.size() != 0 , "filetextarray empty\n");

			uint32_t i = 0;
			while ( i < count ) {
				for (auto line : filetextarray) {
					auto linearray = split(line, ',');
					check(linearray.size() == 3, "linearray len not 3");

					string pattern = linearray[0];
					string text = linearray[1];
					string result  = linearray[2];
					bool lres = false;

					if (result.substr(0, 4) == "TRUE") {
						lres = true;
					} else if (result.substr(0, 5) == "FALSE") {
						lres = false;
					} else {
						check(false, "defined result error");
					}

					bool rres = test_regex_match(text, pattern);
					//printf("get result %u, should be %u\n", rres, lres);
					check(rres == lres , "result expect error");
				}

				i++;
			}

			return 1;
		}
};

extern "C" {
void ontio_debug(const char *ptr, uint32_t len) {
	return;
}

void ontio_panic(const char *ptr, uint32_t len) {
	char *p = (char *) 0x1fffffff;
	*p = 0;
}
}


extern "C" void invoke(void) {
	hello t;
	t.performance_test(100);
	//check(true, "hello steven");
}
