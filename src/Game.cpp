#include "Game.h"

void GameUtils::DrawFps(Color color) {
    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 30, color);
}
void GameUtils::AnimatedCursor(Vector2 pos, float dt) {
    static int8 cursorIndex = 0;
    cursorIndex = (cursorIndex + 1) % 4;
    DrawTexture(MiscAssets::cursors[cursorIndex], pos.x, pos.y, WHITE);
}


void Game::SwitchPauseState() {
    if (GameUI::getUIState() != NONE || _gameState != EXPLORING) return;
        
    if (IsKeyPressed(KEY_ESCAPE)) {
        __isGamePaused = !__isGamePaused;
    }
}
void Game::DrawPauseState() {
    if (__isGamePaused) {
        ClearBackground(LIGHTGRAY);
        DrawRectangle(0, 0, ScreenSettings::w, ScreenSettings::h, Fade(GRAY, 0.5f));

        int8 textSize = 30;
        DrawText("Paused", ScreenSettings::centerX - textSize, ScreenSettings::centerY - textSize, textSize, RED);
    }
}

void Game::DrawStars(Star &stars, float fallSpeed) {
    stars.Draw();
    stars.Fall(fallSpeed);
    stars.Update();
}

void Game::InitMap(Map &map) {
    Vector2 basePos = { 0, 0 };
    map = Map(Paths::Visual::Maps::first, basePos, WHITE);
}
void Game::UpdateMap(Map &map) {
    ClearBackground(BLACK);
    map.render();
}

void Game::InitCam(Camera2D &main) {
    main.rotation = 0;
    main.zoom = 1;
    main.offset = { ScreenSettings::centerX, ScreenSettings::centerY };
}
void Game::UpdateCam(Camera2D &main, Player &player) {
    main.target = { player.getPos().x, player.getPos().y };
    main.offset = { ScreenSettings::centerX, ScreenSettings::centerY };
}

void Game::InitPlayer(Player &player, Map &map) {
    Vector2 playerPos = Vector2(map.getMapCenterX() * 0.5f, map.getMapCenterY());
    Stats playerStats = { 
        .mana = IPS::mana, .hp = IPS::hp, .atk = IPS::atk, .def = IPS::def, 
        .edb = IPS::edb, .edr = IPS::edr, 
        .cr = IPS::cr, .cd = IPS::cd, .cdr = IPS::cdr
    };
    float moveSpeed = 1000;
    player = Player(*Paths::Entity::Player::wipungUp, playerPos, playerStats, WHITE, moveSpeed);
}
void Game::UpdatePlayer(Player &player, Map &map, float dt) {
    player.restrictMovement(map.getW(), map.getH());
    if (GameUI::getUIState() == NONE) { player.move(dt); }
    player.updateStats();
    player.drawShadows();
    player.draw();
}

void Game::InitFoe(Foe &foe, Map &map) {
    Vector2 foePos = Vector2(map.getMapCenterX(), map.getMapCenterY());
    Stats foeStats = EnemyStats::first;
    foe = Foe(Paths::Entity::Enemy::idleK[0], foePos, foeStats, WHITE);
}
void Game::UpdateFoe(Foe &foe) {
    foe.draw();
}

void Game::DrawUI(Player &player, Vector2 &mousePos) {
    GameUI::updateButtons();

    auto availableGear = player.getAvailableGear();
    auto &currentGear = player.getCurrentGear();
    auto &currentWeapon = player.getCurrentWeapon();

    switch (GameUI::getUIState()) {
        case INVENTORY:
            Inventory::drawGear<availableGear.size()>(availableGear);
            Inventory::drawCurrentGear(currentGear);
            Inventory::drawWeapons(currentWeapon, mousePos);
            Inventory::drawCurrentWeapon(currentWeapon);
            Inventory::drawLeftInventory();
            Inventory::drawRightInventory(player);
            break;
    }
}
void Game::HandleUI(Player &player, Vector2 &mousePos) {
    GameUI::changeUIState(mousePos);
    GameUI::handleUIState();

    auto availableGear = player.getAvailableGear();
    auto &currentGear = player.getCurrentGear();
    auto &currentWeapon = player.getCurrentWeapon();

    Inventory::selectGear<availableGear.size()>(availableGear, currentGear, mousePos);
    Inventory::selectWeapon(currentWeapon, 2, mousePos);
    Inventory::selectInventoryTabs(mousePos);
    Inventory::exitInventory(mousePos, GameUI::getUIState());
}

bool Game::BattleEnterAnimation(Camera2D &cam, Player &player, Foe &enemy, float dt) {
    Rectangle playerRect = player.getRect();
    Rectangle enemyRect = enemy.getRect();
    static float targetZoom = 3.f;

    Rectangle fadingRect = { .x = 0, .y = 0, .width = ScreenSettings::w, .height = ScreenSettings::h };
    static float startFade = 0.5f, targetFade = 0.8f;

    if (CheckCollisionRecs(playerRect, enemyRect)) {
        player.setCanMove(false);
        player.setDir(IDLE);

        if (cam.zoom != targetZoom) {
            cam.zoom += 3.f * dt;
            if (cam.zoom > targetZoom) cam.zoom = targetZoom;
        }

        if (startFade <= targetFade) {
            startFade += 1.1f * dt;
            DrawRectangle(fadingRect.x, fadingRect.y, fadingRect.width, fadingRect.height, Fade(BLACK, startFade));
            if (startFade > targetZoom) startFade = targetFade;
        }
    }
    startFade = 0.5f;
    return cam.zoom == targetZoom;
}
void Game::StartBattle(Camera2D &cam, Player &player, Foe &enemy, float dt) {
    if (BattleEnterAnimation(cam, player, enemy, dt)) { 
        _gameState = INBATTLE; 
    }
}

void Game::UpdateActionBox(ActionBox &actionBox, Vector2 &mousePos) {
    actionBox.update();
    actionBox.draw(Fade(WHITE, 0.5f));
    actionBox.handleOptions();
    actionBox.selectOptions(mousePos);
    actionBox.handleSelectSound(mousePos);
}
void Game::UpdateGauges(InitEntityData &initEntityData, Player &player, Foe &enemy) {
    Rectangle playerHpRect = {
        .x = ScreenSettings::w * 0.25f, .y = ScreenSettings::h / 10,
        .width = ScreenSettings::w * 0.2f, .height = ScreenSettings::h / 20
    };
    Rectangle enemyHpRect = {
        .x = ScreenSettings::w - playerHpRect.x - playerHpRect.width, .y = playerHpRect.y,
        .width = playerHpRect.width, .height = playerHpRect.height
    };

    Rectangle playerManaRect = {
        .x = playerHpRect.x, .y = playerHpRect.y + (ScreenSettings::h * 0.05f),
        .width = playerHpRect.width, .height = playerHpRect.height - (playerHpRect.height * 0.5f)
    };

    Rectangle enemyManaRect = {
        .x = enemyHpRect.x, .y = enemyHpRect.y + (ScreenSettings::h * 0.05f),
        .width = playerManaRect.width, .height = playerManaRect.height
    };


    auto playerCurrentHp = player.getStat().hp;
    auto playerCurrentMana = player.getStat().mana;

    auto enemyCurrentHp = enemy.getStat().hp;
    auto enemyCurrentMana = enemy.getStat().mana;

    Gauge::drawGauge(initEntityData.playerHP, playerCurrentHp, playerHpRect, RED);
    Gauge::updateGauge(initEntityData.playerHP, playerCurrentHp);
    Gauge::drawGauge(initEntityData.playerMANA, playerCurrentMana, playerManaRect, BLUE);
    Gauge::updateGauge(initEntityData.playerMANA, playerCurrentMana);

    Gauge::drawGauge(initEntityData.enemyHP, enemyCurrentHp, enemyHpRect, RED);
    Gauge::updateGauge(initEntityData.enemyHP, enemyCurrentHp);
    Gauge::drawGauge(initEntityData.enemyMANA, enemyCurrentMana, enemyManaRect, BLUE);
    Gauge::updateGauge(initEntityData.enemyMANA, enemyCurrentMana);
}

void Game::ProcessBattleUi(ActionBox &actionBox, Star &stars, InitEntityData &initEntityData, Player &player, Foe &enemy, Vector2 &mousePos) {
    ClearBackground(DEEPBLUE);
    DrawStars(stars, 2.f);
    UpdateGauges(initEntityData, player, enemy);
   
    UpdateActionBox(actionBox, mousePos);
}
void Game::ProcessBattleLogic(ActionBox &actionBox, Battle &battle, Player &player, Foe &enemy, Vector2 &mousePos, Camera2D &main) {
    battle.updateEntities(player, enemy);
    battle.manageInternalOption(actionBox, mousePos);
    battle.handleBattleAnimations(actionBox, player, enemy, _gameState);
    battle.battleLoop(player, enemy, _gameState, mousePos);
    battle.updateState(player, enemy, _gameState, main);
}

void Game::GenerateNextMap(Map &map, Battle &battle) {
    auto &level = battle.getBattleData().currentLevel;
    Color baseColor = RAYWHITE;
    switch (level) {
        case 2: map.setColor(Fade(baseColor, 0.1f)); break;
        case 3: map.setColor(Fade(baseColor, 0.2f)); break;
        case 4: map.setColor(Fade(baseColor, 0.3f)); break;
        case 5: map.setColor(Fade(baseColor, 0.4f)); break;
        case 6: map.setColor(Fade(baseColor, 0.5f)); break;
        case 7: map.setColor(Fade(baseColor, 0.6f)); break;
        case 8: map.setColor(Fade(baseColor, 0.7f)); break;
        case 9: map.setColor(Fade(baseColor, 0.8f));; break;
        case 10: map.setColor(Fade(baseColor, 0.9f)); break;
    }
}
void Game::GenerateNextEnemy(Battle &battle, Foe& enemy) {
    auto &level = battle.getBattleData().currentLevel;
    switch (level) {
        case 2: enemy.setStats(EnemyStats::second);  enemy.setColor(GREEN); break;
        case 3: enemy.setStats(EnemyStats::third);   enemy.setColor(DARKGREEN); break;
        case 4: enemy.setStats(EnemyStats::fourth);  enemy.setColor(YELLOW); break;
        case 5: enemy.setStats(EnemyStats::fifth);   enemy.setColor(GOLD); break;
        case 6: enemy.setStats(EnemyStats::sixth);   enemy.setColor(ORANGE); break;
        case 7: enemy.setStats(EnemyStats::seventh); enemy.setColor(BROWN); break;
        case 8: enemy.setStats(EnemyStats::eighth); enemy.setColor(RED); break;
        case 9: enemy.setStats(EnemyStats::ninth);  enemy.setColor(VIOLET); break;
        case 10: enemy.setStats(EnemyStats::tenth); enemy.setColor(RED); break;
    }
}

void Game::GetEntityData(InitEntityData &initEntityData, Player &player, Foe &enemy) {
    initEntityData.playerHP = player.getStat().hp;
    initEntityData.enemyHP = enemy.getStat().hp;
}
void Game::UpdateEntityData(Player &player, Foe &enemy) {
    Stats foeStats = EnemyStats::first;
    enemy.setStats(foeStats);
    player.getStatRef().mana = 100;
}

void Game::Menu() {
    init_seed

    bool started = false, exited = false;
    MainMenu menu(BLACK, 731, 1000, WHITE);

    while (running && !started && !exited) {
        BeginDrawing();
        ScreenSettings::Update();
        float dt = GetFrameTime();
        Vector2 mousePos = { GetMouseX(), GetMouseY() };
	
            menu.Update(dt);
            menu.Display();
            started = menu.StartGame(mousePos);
            exited = menu.ExitGame(mousePos);

        AnimatedCursor(mousePos, dt);
        EndDrawing();
    }

    if (started) Run();
}

void Game::Run() {
    init_seed

    Map map;
    Camera2D mainCamera;
    Player player;
    Foe enemy;

    InitMap(map);
    InitCam(mainCamera);
    InitPlayer(player, map);
    InitFoe(enemy, map);

    Star stars(Paths::Visual::Particles::star, 100);

    InitEntityData initEntityData;
    Battle battle;
    ActionBox actionBox;

    while (running) {
        BeginDrawing();
      
        ScreenSettings::Update();
        float dt = GetFrameTime();
        Vector2 mousePos = { GetMouseX(), GetMouseY() };
  
        switch (_gameState) {
            case EXPLORING:
                GetEntityData(initEntityData, player, enemy);
                UpdateEntityData(player, enemy);

                GenerateNextMap(map, battle);
                GenerateNextEnemy(battle, enemy);

                BeginMode2D(mainCamera);
                    UpdateMap(map);
                    UpdateFoe(enemy);
                    UpdatePlayer(player, map, dt);
                    UpdateCam(mainCamera, player);
                    StartBattle(mainCamera, player, enemy, dt);
                EndMode2D();

                DrawUI(player, mousePos);
                HandleUI(player, mousePos);
                DrawPauseState();
                break;
            case INBATTLE:
                ProcessBattleLogic(actionBox, battle, player, enemy, mousePos, mainCamera);
                ProcessBattleUi(actionBox, stars, initEntityData, player, enemy, mousePos);
                break;
        }

        AnimatedCursor(mousePos, dt);
        SwitchPauseState();
        EndDrawing();
    }
}