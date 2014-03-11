local vec1 = Vision.hkvVec3(0,1000,0)

function OnThink(self)
	self:GetComponentOfType("vHavokRigidBody"):ApplyForce(vec1, Timer:GetThinkInterval())
end
