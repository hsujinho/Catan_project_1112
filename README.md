# Catan_project_1112

此專案為 1112 學期的程式設計課程專案，主題為卡坦島（Catan）桌遊。

## 組員名單

| 組員姓名 | 學號 |
| :--------:| :----: |
| 徐政皓 | 40947043S |
| 陳柏瑜 | 41047054S |
| 洪維駿 | 40923205L |

### 分工

- 徐政皓
  - 程式架構設計
  - 地圖設計
  - SDL 介面設計
  - 遊戲初始化
  - 盜賊相關功能
- 陳柏瑜
- 洪維駿

## 安裝

由於此程式使用 SDL 作為顯示介面，因此在編譯之前您必須安裝 SDL2，若您的電腦使用的是 ubuntu，可以在終端機執行以下指令進行安裝：
```shell
sudo apt-get install libsdl2-dev libsdl2-image-dev
```

若您使用其他系統或在安裝上遇到問題（例如：WSL2、Mac），可以進入 SDL 官網查詢如何安裝，連結網址如下：
https://www.libsdl.org/

常見問題：

1. `Package sdl2_image was not found in the pkg-config search path.` :  
    您可以嘗試執行 `sudo find / -name "sdl2_image.pc" `搜尋電腦中是否有 sdl2_image.pc 檔案。有時它會叫做 SDL2_image.pc，您可以使用 `sudo mv` 來重新命名。
2. Different OS
    此程式預設在 Linux 平台執行，在其他作業系統執行可能會遇到其他問題
    若因此遇到問題，請試著尋找是否有相關需求程式、軟體尚未安裝

## 運行

完畢後，在終端機移動到程式所在目錄並輸入 `make` 進行編譯，之後執行 `./main` 就可以開始進行遊戲了。

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

遊戲正式開始後，程式會依玩家的順序，讓玩家進行回合。每個玩家的回合中，會執行以下動作（部分動作可選擇跳過）：

* **擲骰子（回合開始必須執行）**
* 交易
* 建造
* 使用發展卡
* **結束回合**
  
##### 擲骰子

在擲骰子的階段，程式會隨機產生兩個 1 到 6 的數字，並將兩個數字相加，作為此回合的骰子點數。接著，依據骰子點數，分為兩種情況：

1. 骰子點數為 7 點：
    
    1. 此時，所有玩家的資源卡數量若超過 7 張，則必須棄掉一半的資源卡。
   
    2. 接著，程式會讓擲骰玩家選擇一個板塊，將苦力怕移動到該板塊。
   
    3. 最後，程式會讓玩家選擇一個玩家，並將該玩家的一張資源卡隨機拿走。

2. 骰子點數為 2 ~ 12 點，並不為 7 點：
    
   * 此時，程式會將骰子點數與板塊上的數字進行比對，若有符合的板塊，且該板塊上沒有苦力怕，則會將該地圖點上的資源卡發給所有與該地圖點相連的玩家。

##### 交易

在建築階段，玩家可以選擇與銀行或其他玩家交易，若交易成功，則會成功與所選擇對象交易，否則交易失敗。

1. 與玩家交易：
    - 當與其他玩家交易時，其他玩家有權利拒絕與您的交易，若其他玩家拒絕您的交易，則交易失敗
2. 與銀行交易：
    - 與銀行交易時，程式會另外判斷您是否擁有港口，若有則會切換成與港口交易，交易匯率會以您擁有之港口所訂定之匯率更動
    - 港口交易分為兩種：
      1. 對於任意資源皆以 2：1 交換
      2. 對於特定資源以 3：1 交換

> 請注意，若您或交易對象其中一方所擁有資源不足，則交易直接失敗

##### 建造

在建造階段，玩家可以選擇消耗資源建造道路、村莊以及城市三種建築，或購買隨機種類的發展卡。

四種行為的資源消耗如下：

| 建築 | 磚頭 | 木頭 | 羊毛 | 小麥 | 礦石 |
| :--------: | :----: | :----: | :----: | :----: | :----: |
| 道路 | 1 | 1 | 0 | 0 | 0 |
| 村莊 | 1 | 1 | 1 | 1 | 0 |
| 城市 | 0 | 0 | 0 | 2 | 3 |
| 發展卡 | 0 | 1 | 1 | 1 | 0 |

##### 使用發展卡

發展卡分別有下列 4 種：

| 發展卡 | 效果 |
| :--------: | :----: |
| 騎士卡 | 移動盜賊、掠奪資源 |
| 壟斷卡 | 掠奪所有人手上某種特定資源 |
| 獲取資源卡 | 免費從銀行得到兩種資源 |
| 分數卡 | 分數 + 1 |
| 建造道路卡 | 免費建造兩條道路 |

> 請注意，若為這回合買到的發展卡，則不能在該回合使用。

##### 結束回合

### 額外功能

為增加遊戲的趣味性，我們在遊戲中加入了一些額外的功能。

#### 季節

遊戲中有四個季節，分別為春夏秋冬，每個季節都有不同的效果。

### 遊戲結束

當有玩家的分數達到 **10** 分時，遊戲結束，並宣布該玩家獲勝。

## 程式架構

```c
// main.c
// seudo structure of the program, not the real code, including the function name and the parameters

int main(){
    // initialize the variables
    init_game(...);
    // initialize SDL
    init_SDL(...);

    // show the map
    render_map(...);

    // start the game
    while(game_is_not_end){
        // check if any player has 10 VP
        check_winner(...);

        // start a round
        start_round(...);
    }

    // free the memory
    free_game(...);
}
```

### structure

```c
// store the coordinate of a point
typedef struct Point{
    int x;
    int y;
}point;

// store the information of a player
typedef struct Player{
    int id;                        
    int VP;                         // victory point
    int resource[5];                // 0: brick, 1: lumber, 2: wool, 3: grain, 4: ore
    int number_of_knights;          
    int length_of_road;
    int number_of_building[3];      // 0: settlement, 1: city, 2: road
    int number_of_dev_card;         
    bool has_longest_road;
    bool has_most_knights;
    struct list_head *devcard_list; // list of devcard in player's hand
}player;

// store the information of a piece
typedef struct Piece{
    point p;            // coordinate of the piece
    int eco_type;       // 0: hill, 1: forest, 2: pasture, 3: field, 4: mountain, 5: desert
    int number;         // the point number of the piece
    bool robberFlag;    // true: robber is on the piece, false: robber is not on the piece
}piece;

// store the information of a land between pieces
typedef struct LandBetween{
    point p;            // coordinate of the land between pieces
    int type;           // type of port, or nothing special
    bool has_building;  
    int owner;          // owner of the building
    int building;       // 0: settlement, 1: city
}landbetween;

// store the information of a road
typedef struct Road{    
    point start;    // coordinate of the start point (upper point)
    point end;      // coordinate of the end point (lower point)
    int owner;      // owner of the road
    int dir;        // direction of the road, 0: left down, 1: right down, 2: down
}road;

// store the information of a development card
typedef struct DevCard{
    int type;               // 0: knight, 1: monopoly, 2: road building, 3: year of plenty, 4: victory point
    bool used;              
    struct list_head node;  // node of the list
}devcard;

// store the information of the map
typedef struct mapInfo{
    player **players;
    piece **pieces;
    landbetween **lands;
    road **roads;
    struct list_head *devcards; 
}mapInfo;
```

## 程式碼說明

### 交易

`void trade_action( mapInfo *info, int32_t id );`
> Trade action list. After selection, `trade_action` will call corresponding functions
- Input
  - `info`	    : game information
  - `id`	    : player id who wants to trade
- Output
  - No

`void trade_with_bank( player *player_A, landbetween **maps );`
> Trade with bank
- Input
  - `player_A`    : player who wants to trade
  - `maps`	    : game information
- Output
  - No

`void trade_with_player( player *candidate, player *player_A );`
> Trade with player
- Input
  - `player_A`    : player who wants to trade
  - `candidate`   : player that player_A wants to trade with
- Output
  - No

`int32_t trade_with_port( player *player_A, landbetween **maps, int32_t get_choice );`
> Find the exchange rate `player_A` can trade with bank.
- Input
  - `player_A`    : player who wants to trade
  - `maps`	    : game information
  - `get_choice`  : resource player_A wants to get
- Return value
  - The exchange rate if `player_A` has certain port
  - If `player_A` has no port or related port, the return value is default to 4

### 發展卡

`void dev_card_action( SDL_Renderer *renderer, mapInfo *info, int id );`
> devcard action list. After selection, `dev_card_action` will call corresponding functions.
- Input
  - `renderer`  : map
  - `info`	    : game information
  - `id`	      : player id who wants to trade
- Output
  - No

`void monopoly_action( mapInfo *info, int id );`
> Monopoly. Take away one certain resource from all the other player's hand.
- Input
  - `id`    : player id of player who wants to trade
  - `info`	: game information
- Output
  - No

`int32_t year_of_plenty_action( mapInfo *info, int id );`
> Year of plenty. Freely get 2 resource from the bank.
- Input
  - `id`    : player id of player who wants to trade
  - `info`	: game information
- Output
  - No

`void dev_point_action( mapInfo *info, int id );`
> Devcard point. Freely get one point.
- Input
  - `id`    : player id of player who wants to trade
  - `info`	: game information
- Output
  - No
