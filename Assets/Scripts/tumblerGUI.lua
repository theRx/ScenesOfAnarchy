function OnBeforeSceneLoaded()
  Timer:SetFrozen(true)
end

function OnAfterSceneLoaded(self)
	GUI:LoadResourceFile("Dialogs/MenuSystem.xml")
  G.myDialog = GUI:ShowDialog("Dialogs/TumblerMenuLUA.xml")
  GUI:SetCursorVisible(true)
end

function OnBeforeSceneUnloaded()
	local mode = Application:GetEditorMode()
  if mode == Vision.EDITOR_PLAY or mode == Vision.EDITOR_RUN then
    GUI:SetCursorVisible(false)
    GUI:CloseDialog(G.myDialog)
  end
  Timer:SetFrozen(false)
end
