#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// 等待圖 (以鄰接矩陣表示)
int WFG[MAX_PROCESSES][MAX_PROCESSES];
int visited[MAX_PROCESSES];     // 訪問標記
int stack[MAX_PROCESSES];       // 用來追蹤當前路徑的堆疊
int numProcesses;

// 檢測等待圖中是否存在循環的函式
int detectCycle(int process) {
    visited[process] = 1;   // 標記該節點為已訪問
    stack[process] = 1;     // 將該節點加入當前路徑堆疊

    for (int i = 0; i < numProcesses; i++) {
        if (WFG[process][i]) {  // 如果存在從 process 到 i 的邊
            if (!visited[i]) {  // 如果節點 i 尚未訪問
                if (detectCycle(i)) {
                    return 1;   // 發現循環
                }
            } else if (stack[i]) {
                return 1;       // 發現循環 (回邊)
            }
        }
    }

    stack[process] = 0;    // 將節點從當前路徑堆疊中移除
    return 0;
}

// 檢測死鎖的主函式
void detectDeadlock() {
    // 初始化訪問標記與堆疊
    for (int i = 0; i < numProcesses; i++) {
        visited[i] = 0;
        stack[i] = 0;
    }

    // 對每個未訪問的節點進行循環檢測
    for (int i = 0; i < numProcesses; i++) {
        if (!visited[i]) {
            if (detectCycle(i)) {
                printf("偵測到死鎖，涉及的進程為 P%d\n", i + 1);
                return;
            }
        }
    }

    printf("未偵測到死鎖。\n");
}

int main() {
    // 輸入進程數量
    printf("請輸入進程數量：");
    scanf("%d", &numProcesses);

    // 輸入等待圖的鄰接矩陣
    printf("請輸入等待圖的鄰接矩陣 (0 表示無邊，1 表示有邊)：\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numProcesses; j++) {
            scanf("%d", &WFG[i][j]);
        }
    }

    // 檢測死鎖
    detectDeadlock();

    return 0;
}
