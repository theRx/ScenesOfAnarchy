_G.rotVec = Vision.hkvVec3(0,0,0)

function OnAfterSceneLoaded(self)

self.map = Input:CreateMap("speedControlMap")
  self.map:MapTrigger("Faster", "KEYBOARD", "CT_KB_Z")
  self.map:MapTrigger("Slower", "KEYBOARD", "CT_KB_X")
  
end


function OnThink(self)

  --self:SetRotationDelta(rotVec)
  self:GetComponentOfType("vHavokRigidBody"):SetAngularVelocity(_G.rotVec)
  
  if self.map:GetTrigger("Faster") == 1 then
    _G.rotVec.y = _G.rotVec.y + 1
  elseif self.map:GetTrigger("Slower") == 1 then
    _G.rotVec.y = _G.rotVec.y - 1
  end

  if _G.rotVec.y > 100 then
    _G.rotVec.y = 100
  elseif _G.rotVec.y < -100 then
    _G.rotVec.y = -100
  end
  
end
