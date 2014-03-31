rotVec = Vision.hkvVec3(0,0,0)

function OnAfterSceneLoaded(self)

self.map = Input:CreateMap("speedControlMap")
  self.map:MapTrigger("Faster", "KEYBOARD", "CT_KB_Z")
  self.map:MapTrigger("Slower", "KEYBOARD", "CT_KB_X")
  
end


function OnThink(self)

  --self:SetRotationDelta(rotVec)
  self:GetComponentOfType("vHavokRigidBody"):SetAngularVelocity(rotVec)
  
  if self.map:GetTrigger("Faster") == 1 then
    rotVec.y = rotVec.y + 1
  elseif self.map:GetTrigger("Slower") == 1 then
    rotVec.y = rotVec.y - 1
  end

  if rotVec.y > 50 then
    rotVec.y = 50
  elseif rotVec.y < -50 then
    rotVec.y = -50
  end
  
end
