local rotVec = Vision.hkvVec3(0,0,0)

function OnThink(self)
  self:GetComponentOfType("vHavokRigidBody"):SetAngularVelocity(rotVec)  --ApplyTorque(rotVec, Timer:GetThinkInterval())
end
