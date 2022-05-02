#include <iostream>

using namespace std;

int n;

void print(int p, string str)
{
	for(int i=0; i<4*p; i++) cout << "_";
	cout << str << '\n';
}

void solve(int p)
{
	if(p == n){
		print(p, "\"재귀함수가 뭔가요?\"");
		print(p, "\"재귀함수는 자기 자신을 호출하는 함수라네\"");
		print(p, "라고 답변하였지.");
		return; 
	}
	
	print(p, "\"재귀함수가 뭔가요?\"");
	print(p, "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.");
	print(p, "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.");
	print(p, "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"");
	
	solve(p+1);
	
	print(p, "라고 답변하였지."); 
}

int main()
{
	cin >> n;
	
	cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n";
	solve(0);
	
	return 0;
}
