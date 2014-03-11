rotVec = Vision.hkvVec3(0,250,0)

function OnThink(self)
  if Input:IsKeyPressed(Vision.KEY_Z) then
    rotVec += 200
  elseif Input:IsKeyPressed(Vision.KEY_C) then
    rotVec -= 200
  end


end
