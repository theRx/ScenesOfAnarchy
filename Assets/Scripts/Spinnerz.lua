rotVec = Vision.hkvVec3(0,1,0)
--m_tumbler = Game:GetEntity("TumblerMachine"):GetComponentOfType("vHAvokRigidBody")
--m_tumbler = self

function OnAfterSceneLoaded(self)
	self.map = Input:CreateMap("speedControlMap")
  self.map:MapTrigger("Faster", "KEYBOARD", "CT_KB_Z")
  self.map:MapTrigger("Slower", "KEYBOARD", "CT_KB_X")
  --m_tumbler = self:GetComponentOfType("VisObject3D_cl ")
end


function OnThink(self)

  self:SetRotationDelta(rotVec)
  --self:GetComponentOfType("VisObject3D_cl"):SetRotationDelta(rotVec)

  if self.map:GetTrigger("Faster") == 1 then
    rotVec.y = rotVec.y + 1
  elseif self.map:GetTrigger("Slower") == 1 then
    rotVec.y = rotVec.y - 1
  end

  if rotVec.y > 5 then
    rotVec.y = 5
  elseif rotVec.y < -5 then
    rotVec.y = -5
  end
--  self:GetComponentOfType("vHavokRigidBody"):ApplyTorque(rotVec, Timer:GetTimeDiff())
--  self:GetComponentOfType("vHavokRigidBody"):ApplyAngularImpulse(rotVec)
end