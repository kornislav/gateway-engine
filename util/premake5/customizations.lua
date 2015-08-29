premake.override(premake.vstudio.vc2010, 'platformToolset',
	function(base, cfg)
		-- When compiling for Android using ANT and vs-android we need a special toolset
		-- that is not supported by default in premake
		if cfg.platform == 'Android' then
			toolset = 'arm-linux-androideabi-4.8'
			_p(2,'<PlatformToolset>%s</PlatformToolset>', toolset)
		else
			base(cfg)
		end
end)

premake.override(premake.vstudio, 'projectPlatform',
	function(base, cfg)
		-- Always use the build configuration string.
		return cfg.buildcfg
end)

premake.override(premake.vstudio, 'archFromConfig',
	function(base, cfg, win32)
		-- Premake is weird about this - it prefers to specify an "architecture"
		-- instead of a real platform string, which results in Visual Studio solutions
		-- that don't map to project platforms at all. Always use the platform, instead.
		return cfg.platform
end)

premake.override(premake.vstudio, 'getLinks',
	function(base, cfg, explicit)
		-- This portion is taken from the original premake source but modified slightly.

		-- System libraries are undecorated, add the required extension
		local links = premake.config.getlinks(cfg, "system", "fullpath")

		if cfg.platform == "Win32" then
			for i = 1, #links do
				links[i] = path.appendextension(links[i], ".lib")
			end
		end

		-- If we need sibling projects to be listed explicitly, add them on
		if explicit then
			local siblings = premake.config.getlinks(cfg, "siblings", "fullpath")
			links = table.join(links, siblings)
		end

		return links
end)