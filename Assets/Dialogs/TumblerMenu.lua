local fiveBalls = false
local tenBalls = false
local fifteenBalls = false
local twentyBalls = false
local twentyFiveBalls = false
local thrityBalls = false
local thirtyFiveBalls = false

local ballCount = 0
local keyID --String

--A whole mess for static ball spawn points
local ballArray = {}
ballArray[1] = {0, 113}
ballArray[2] = {-111, 175}
ballArray[3] = {115, 172}
ballArray[4] = {0, 0}
ballArray[5] = {-111, 61}
ballArray[6] = {115, 59}
ballArray[7] = {-313, 160}
ballArray[8] = {329, 54}
ballArray[9] = {-142, -325}
ballArray[10] = {115, -296}
ballArray[11] = {-111, -55}
ballArray[12] = {0, -114}
ballArray[13] = {115, -55}
ballArray[14] = {-107, 288}
ballArray[15] = {134, 295}
ballArray[16] = {-210, 120}
ballArray[17] = {222, 95}
ballArray[18] = {-210, -118}
ballArray[19] = {-111, -180}
ballArray[20] = {115, -171}
ballArray[21] = {222, -124}
ballArray[22] = {-210, 254}
ballArray[23] = {222, 228}
ballArray[24] = {213, 164}
ballArray[25] = {222, -249}
ballArray[26] = {-217, -243}
ballArray[27] = {-313, -173}
ballArray[28] = {-313, -54}

local depthArray = {-193, -80, 39, 156, 272}

function OnItemClicked(self, item, buttons, x, y)
  if (item:GetID() == GUI:GetID("SPEED0")) then
	  self:SetVisible(false)
    GUI:SetCursorVisible(false)
    BallSpawn()
    _G.rotVec = Vision.hkvVec3(0,0,0)
    Timer:SetFrozen(false)
    elseif (item:GetID() == GUI:GetID("SPEED1")) then
	  self:SetVisible(false)
    GUI:SetCursorVisible(false)
    BallSpawn()
    _G.rotVec = Vision.hkvVec3(0,20,0)
    Timer:SetFrozen(false)
  elseif (item:GetID() == GUI:GetID("SPEED2")) then
	  self:SetVisible(false)
    GUI:SetCursorVisible(false)
    BallSpawn()
    _G.rotVec = Vision.hkvVec3(0,40,0)
    Timer:SetFrozen(false)
  elseif (item:GetID() == GUI:GetID("SPEED3")) then
	  self:SetVisible(false)
    GUI:SetCursorVisible(false)
    BallSpawn()
    _G.rotVec = Vision.hkvVec3(0,60,0)
    Timer:SetFrozen(false)
  elseif (item:GetID() == GUI:GetID("SPEED4")) then
	  self:SetVisible(false)
    GUI:SetCursorVisible(false)
    BallSpawn()
    _G.rotVec = Vision.hkvVec3(0,80,0)
    Timer:SetFrozen(false)
  elseif (item:GetID() == GUI:GetID("SPEED5")) then
	  self:SetVisible(false)
    GUI:SetCursorVisible(false)
    BallSpawn()
    _G.rotVec = Vision.hkvVec3(0,100,0)
    Timer:SetFrozen(false)

  elseif (item:GetID() == GUI:GetID("CHECKBOX1")) then
	  fiveBalls = not fiveBalls
  elseif (item:GetID() == GUI:GetID("CHECKBOX2")) then
	  tenBalls = not tenBalls
  elseif (item:GetID() == GUI:GetID("CHECKBOX3")) then
	  fifteenBalls = not fifteenBalls
  elseif (item:GetID() == GUI:GetID("CHECKBOX4")) then
	  twentyBalls = not twentyBalls
  elseif (item:GetID() == GUI:GetID("CHECKBOX5")) then
	  twentyFiveBalls = not twentyFiveBalls
  elseif (item:GetID() == GUI:GetID("CHECKBOX6")) then
	  thirtyBalls = not thirtyBalls
  elseif (item:GetID() == GUI:GetID("CHECKBOX7")) then
	  thirtyFiveBalls = not thirtyFiveBalls
  end
   
end

function BallSpawn()


  --Spawning set 1
  if fiveBalls == true then
    i=1 --Just for uniformity
    SpawnLoop(ballArray[i][1],ballArray[i][2])
  end

  --Spawning set 2
  if tenBalls == true then
    for i=2, 3 do
      SpawnLoop(ballArray[i][1],ballArray[i][2])
    end
  end

  --Spawning set 3
  if fifteenBalls == true then
    for i=4, 6 do
      SpawnLoop(ballArray[i][1],ballArray[i][2])
    end
  end

  --Spawning set 4
  if twentyBalls == true then
    for i=7, 10 do
      SpawnLoop(ballArray[i][1],ballArray[i][2])
    end
  end

  --Spawning set 5
  if twentyFiveBalls == true then
    for i=11, 15 do
      SpawnLoop(ballArray[i][1],ballArray[i][2])
    end
  end

  --Spawning set 6
  if thirtyBalls == true then
    for i=16, 21 do
      SpawnLoop(ballArray[i][1],ballArray[i][2])
    end
  end

  --Spawning set 7
  if thirtyFiveBalls == true then
    for i=22, 28 do
      SpawnLoop(ballArray[i][1],ballArray[i][2])
    end
  end

end

function SpawnLoop(x, z)
  for y=1, 5 do
    keyID="ball"..ballCount
    ballCount = ballCount + 1
    entity = Game:CreateEntity(Vision.hkvVec3(x, depthArray[y], z),"VisBaseEntity_cl","Models/MagicBall.model",keyID)
    entity:SetScaling(7)
    entity:AddComponentOfType("vHavokRigidBody","RigidBody")
    entity.RigidBody:SetMass(0.1)
    entity.RigidBody:SetRestitution(0.4)
    entity.RigidBody:SetFriction(0.5)
    Debug:PrintLine(entity:GetKey())
  end

end