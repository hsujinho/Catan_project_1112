# Catan_project_1112

此專案為 1112 學期的程式設計課程專案，主題為卡坦島（Catan）桌遊。

## 組員名單

| 組員姓名 | 學號 |
| :--------:| :----: |
| 徐政皓   | 40947043S |
| 陳柏瑜 | 41047054S |
| 洪維駿 | 40923205L |

## 安裝

## 運行

## 遊戲指南

此遊戲的運作模式使用 SDL 作為地圖顯示的介面，並使用終端機做為遊戲的操作介面，輸入各種資料以進行遊戲。

遊戲全程中，玩家將作為編號為 1 的玩家進行遊戲。而編號 2, 3, 4 的玩家為電腦玩家，其操作為電腦自動進行。

各玩家編號及其對應的顏色如下：
| 玩家編號 | 顏色 |
| :--------: | :----: |
| 1 | <span style="color: red"> 紅色|
| 2 | 白色 |
| 3 | <span style="color: orange">橘色 |
| 4 | <span style="color: blue">藍色 |

### 遊戲階段
#### 遊戲開始

遊戲開始後，程式會將卡坦島的地圖初始化，並隨機分配地形及數字給每個地圖點，並顯示地圖在 SDL 的視窗上。接著，程式會隨機選擇一位玩家作為起始玩家，並由起始玩家開始進行遊戲。

接下來，程式會依玩家的順序，讓玩家建造第一個村莊及道路，接著反著剛剛的順序，讓玩家再建造第二個村莊及道路，並拿取初始資源。當所有玩家都完成動作後，遊戲進入正式的遊戲階段。

#### 回合階段

遊戲正式開始後，程式會依玩家的順序，讓玩家進行回合。每個玩家的回合中，會依序執行以下動作（部分動作可選擇跳過）：

1. 擲骰子
2. 交易
3. 建造
4. 結束回合

##### 擲骰子

在擲骰子的階段，程式會隨機產生兩個 1 到 6 的數字，並將兩個數字相加，作為此回合的骰子點數。接著，依據骰子點數，分為兩種情況：

1. 骰子點數為 7 點：
    
    1. 此時，所有玩家的資源卡數量若超過 7 張，則必須棄掉一半的資源卡。
   
    2. 接著，程式會讓擲骰玩家選擇一個板塊，將苦力怕移動到該板塊。
   
    3. 最後，程式會讓玩家選擇一個玩家，並將該玩家的一張資源卡隨機拿走。

2. 骰子點數為 2 ~ 12 點，並不為 7 點：
    
   * 此時，程式會將骰子點數與板塊上的數字進行比對，若有符合的板塊，且該板塊上沒有苦力怕，則會將該地圖點上的資源卡發給所有與該地圖點相連的玩家。

##### 交易

##### 建造

##### 結束回合

### 遊戲結束

當有玩家的分數達到 10 分時，遊戲結束，並宣布該玩家獲勝。

## 程式架構

### 程式流程圖

### 程式架構圖

### 程式碼說明

