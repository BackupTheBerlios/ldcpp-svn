#include "stdinc.h"
#include "DCPlusPlus.h"
#include "ResourceManager.h"
string ResourceManager::strings[] = {
"Active", 
"Enabled / Search String", 
"&Add", 
"Add To Favorites", 
"Added", 
"Automatic Directory Listing Search", 
"Destination Directory", 
"Discard", 
"Download Matches", 
"Enabled", 
"Full Path", 
"ADLSearch Properties", 
"Search String", 
"Max FileSize", 
"Min FileSize", 
"Search Type", 
"Size Type", 
"All download slots taken", 
"All %d users offline", 
"All 3 users offline", 
"All 4 users offline", 
"All", 
"Any", 
"At least", 
"At most", 
"Audio", 
"Auto connect / Name", 
"Auto grant slot / Nick", 
"Average/s: ", 
"AWAY", 
"Away mode off", 
"Away mode on: ", 
"B", 
"Ban user(s)", 
"Both users offline", 
"B/s", 
"Browse...", 
"&Browse...", 
"Browse file list", 
"Certificate not trusted, unable to connect", 
"TLS disabled, failed to generate certificate: ", 
"Choose folder", 
"CID", 
"Close", 
"Close connection", 
"Closing connection...", 
"Compressed", 
"Error during compression", 
"Maximum command length exceeded", 
"&Configure", 
"&Connect", 
"Connect to hub", 
"Connected", 
"Connecting...", 
"Connecting (forced)...", 
"Connecting to ", 
"Connection", 
"Connection closed", 
"Connection timeout", 
"Configured Public Hub Lists", 
"Copy Filename", 
"Copy address to clipboard", 
"Copy magnet link to clipboard", 
"Copy nick to clipboard", 
"Could not open target file: ", 
"Count", 
"Country", 
"CRC Checked", 
"Error during decompression", 
"Description", 
"Destination", 
"Directory", 
"Directory already shared", 
"Directory or directory name already exists", 
"Disk full(?)", 
"Disconnect user(s)", 
"Disconnected", 
"Disconnected user leaving the hub: ", 
"Document", 
"Done", 
"Don't remove /password before your password", 
"The temporary download directory cannot be shared", 
"Download", 
"Download failed: ", 
"Download finished, idle...", 
"Download Queue", 
"Download starting...", 
"Download to...", 
"Download whole directory", 
"Download whole directory to...", 
"Downloaded", 
"Downloaded %s (%.01f%%) in %s", 
" downloaded from ", 
"Downloading...", 
"Downloading public hub list...", 
"Downloading list...", 
"Downloads", 
"Duplicate file will not be shared: ", 
"Dupe matched against: ", 
"Duplicate source", 
"Edit", 
"&Edit", 
"E-Mail", 
"Please enter a nickname in the settings dialog!", 
"Please enter a password", 
"Please enter a reason", 
"Enter search string", 
"Please enter a destination server", 
"Errors", 
"Error creating hash data file: ", 
"Error creating adc registry key", 
"Error creating dchub registry key", 
"Error creating magnet registry key", 
"Error hashing ", 
"Error saving hash data: ", 
"Exact size", 
"Executable", 
"Failed to load certificate file", 
"Failed to load private key", 
"Join/part of favorite users showing off", 
"Join/part of favorite users showing on", 
"Favorite name", 
"Under what name you see the directory", 
"Favorite hub added", 
"Hub already exists as a favorite", 
"This hub is not a favorite hub", 
"Identification (leave blank for defaults)", 
"Favorite Hub Properties", 
"Favorite hub removed", 
"Favorite Hubs", 
"Favorite user added", 
"Favorite Users", 
"File", 
"Files", 
"This file has no TTH", 
"This file is already queued", 
"Subtract list", 
"File list refresh failed: ", 
"File list refresh finished", 
"File list refresh initiated", 
"File list refresh in progress, please wait for it to finish before trying to refresh again", 
"File not available", 
"File type", 
"A file with a different size already exists in the queue", 
"A file with different tth root already exists in the queue", 
"Filename", 
"files left", 
"files/h", 
"F&ilter", 
"Filtered", 
"Find", 
"Finished Downloads", 
"Finished Uploads", 
"File with '$' cannot be downloaded and will not be shared: ", 
"Force attempt", 
"GiB", 
"Get file list", 
"Go to directory", 
"Grant extra slot", 
"Hash database", 
"Creating file index...", 
"Run in background", 
"Statistics", 
"Please wait while DC++ indexes your files (they won't be shared until they've been indexed)...", 
"Unable to read hash data file", 
"Hash database rebuilt", 
"Hashing failed: ", 
"Finished hashing: ", 
"High", 
"Highest", 
"Hit Ratio: ", 
"Hits: ", 
"Hub", 
"Hubs", 
"Address", 
"Hub list downloaded...", 
"Edit the hublist", 
"Name", 
"Hublist", 
"Hub password", 
"Users", 
"Ignore TTH searches", 
"Ignored message: ", 
"Hub address cannot be empty.", 
"Invalid file list name", 
"Invalid number of slots", 
"Invalid target file (missing directory, check default download directory setting)", 
"Full tree does not match TTH root", 
"IP: ", 
"IP", 
"Items", 
"Join/part showing off", 
"Join/part showing on", 
"Joins: ", 
"KiB", 
"KiB/s", 
"Kick user(s)", 
"A file of equal or larger size already exists at the target location", 
"Last change: ", 
"Hub (last seen on if offline)", 
"Time last seen", 
"left", 
"Listening socket failed (you need to restart DC++): ", 
"Loading DC++, please wait...", 
"Lookup TTH at Bitzi.com", 
"Low", 
"Lowest", 
"Filename:", 
"File Hash:", 
"Do nothing", 
"Add this file to your download queue", 
"Do the same action next time without asking", 
"Start a search for this file", 
"A MAGNET link was given to DC++, but it didn't contain a valid file hash for use on the Direct Connect network.  No action will be taken.", 
"DC++ has detected a MAGNET link with a file hash that can be searched for on the Direct Connect network.  What would you like to do?", 
"MAGNET Link detected", 
"Download files from the Direct Connect network", 
"DC++", 
"URL:MAGNET URI", 
"Match queue", 
"Matched %d file(s)", 
"Max Hubs", 
"Max Size", 
"Max Users", 
"Min Size", 
"MiB", 
"MiB/s", 
"MiBits/s", 
"About DC++...", 
"ADL Search", 
"Arrange icons", 
"Cascade", 
"Change Log", 
"Close all file list windows", 
"Close all offline PM windows", 
"Close all PM windows", 
"Close all search windows", 
"Close disconnected", 
"Help &Contents\tF1", 
"DC++ discussion forum", 
"Donate (paypal)", 
"&Download Queue\tCtrl+D", 
"E&xit", 
"Frequently asked questions", 
"&Favorite Hubs\tCtrl+F", 
"Favorite &Users\tCtrl+U", 
"&File", 
"Follow last redirec&t\tCtrl+T", 
"Indexing progress", 
"&Help", 
"Downloads", 
"GeoIP database update", 
"Help forum", 
"Translations", 
"DC++ Homepage", 
"Horizontal Tile", 
"Minimize &All", 
"Restore All", 
"Network Statistics", 
"&Notepad\tCtrl+N", 
"Open downloads directory", 
"Open file list...\tCtrl+L", 
"Match downloaded lists", 
"Open own list", 
"&Public Hubs\tCtrl+P", 
"&Quick Connect ...\tCtrl+Q", 
"&Reconnect\tCtrl+R", 
"Refresh file list\tCtrl+E", 
"Report a bug", 
"Request a feature", 
"&Search\tCtrl+S", 
"Search Spy", 
"Settings...", 
"Show", 
"&Status bar\tCtrl+2", 
"System Log", 
"&Toolbar\tCtrl+1", 
"T&ransfers\tCtrl+3", 
"Vertical Tile", 
"&View", 
"&Window", 
"Min Share", 
"Min Slots", 
"Move/Rename", 
"Move &Down", 
"Move &Up", 
"Network Statistics", 
"&New...", 
"Next", 
"Nick", 
"Your nick was already taken, please change to something else!", 
" (Nick unknown)", 
"TLS disabled, no certificate file set", 
" not shared; calculated CRC32 does not match the one found in SFV file.", 
"No directory specified", 
"You're trying to download from yourself!", 
"Can't download from passive users when you're passive", 
"No errors", 
"No matches", 
"No slots available", 
"No", 
"No users", 
"No users to download from", 
"Normal", 
"Not listening for connections - please restart DC++", 
"Notepad", 
"Offline", 
"Online", 
"Only users with free slots", 
"Only TLS connections allowed", 
"Only results with TTH root", 
"Only where I'm op", 
"Open", 
"Open download page?", 
"Open folder", 
"Operating system does not match minimum requirements for feature", 
"Out of buffer space", 
"Parts: ", 
"Passive user", 
"Password", 
"Path", 
"Paused", 
"PiB", 
"Picture", 
"Port: ", 
"Preparing file list...", 
"Press the follow redirect button to connect to ", 
"Priority", 
"Private message", 
"Private message from ", 
"&Properties", 
"Public Hubs", 
"Purge", 
"Quick Connect", 
"Rating", 
"Ratio", 
"Re-add source", 
"Really exit?", 
"Really remove?", 
"Redirect", 
"Redirect request received to a hub that's already connected", 
"Redirect user(s)", 
"&Refresh", 
"Refresh user list", 
"Reliability", 
"&Remove", 
"Remove all", 
"Remove all subdirectories before adding this one", 
"Remove user from queue", 
"Remove source", 
" renamed to ", 
"Rollback inconsistency, existing file does not match the one being downloaded", 
"Running...", 
"s", 
"Search", 
"Search for", 
"Search for alternates", 
"Search for file", 
"Search options", 
"Search spam detected from ", 
"Search Spy", 
"Search String", 
"Searching for ", 
"Ready to search...", 
"Searching too soon, next search in %i seconds", 
"Request to seek beyond the end of data", 
"Send private message", 
"Separator", 
"Server", 
"Set priority", 
"Settings", 
"Add finished files to share instantly (if shared)", 
"&Add folder", 
"Break on first ADLSearch match", 
"Advanced", 
"Advanced\\Experts only", 
"Advanced resume using TTH", 
"Advanced settings", 
"Allow TLS connections to clients without trusted certificate", 
"Allow TLS connections to hubs without trusted certificate", 
"Use antifragmentation method for downloads", 
"Appearance", 
"Appearance\\Colors and sounds", 
"Autodrop settings", 
"Drop sources below", 
"Check every", 
"Min elapsed", 
"Max inactivity", 
"Min sources online", 
"Min filesize", 
"Autodrop slow sources for all queue items (except filelists)", 
"Remove slow filelists", 
"Don't remove the source when autodropping, only disconnect", 
"Auto-away on minimize (and back on restore)", 
"Automatically follow redirects", 
"Automatically disconnect users who leave the hub", 
"Don't automatically disconnect favorite users who leave the hub", 
"Automatically search for alternative download locations", 
"Automatically match queue for auto search hits", 
"Auto-search limit", 
"Auto-open at startup", 
"Auto refresh time", 
"Bind address", 
"Tab bolding on content change", 
"Advanced\\Security Certificates", 
"&Change", 
"Clear search box after each search", 
"Colors", 
"Command", 
"Enable safe and compressed transfers", 
"Configure Public Hub Lists", 
"Confirm dialog options", 
"Confirm application exit", 
"Confirm favorite hub removal", 
"Confirm item removal in download queue", 
"Connection Type", 
"Default away message", 
"Direct connection", 
"Directories", 
"Don't download files already in the queue", 
"Don't download files already in share", 
"Default download directory", 
"Limits", 
"Downloads", 
"Maximum simultaneous downloads (0 = infinite)", 
"No new downloads if speed exceeds (KiB/s, 0 = disable)", 
"Donate :s! (ok, dirty dollars are fine as well =) (see help menu)", 
"External / WAN IP", 
"Only show joins / parts for favorite users", 
"Downloads\\Favorites", 
"Favorite download directories", 
"Filename", 
"Filter kick and NMDC debug messages", 
"Firewall with manual port forwarding", 
"Firewall (passive, last resort)", 
"Firewall with UPnP", 
"Format", 
"Personal information", 
"Guess user country from IP", 
"Accept custom user commands from hub", 
"Ignore private messages from the hub", 
"Ignore private messages from bots", 
"Incoming connection settings (see Help/FAQ if unsure)", 
"Don't delete file lists when exiting", 
"Language file", 
"Keep duplicate files in your file list", 
"Log downloads", 
"Log filelist transfers", 
"Log main chat", 
"Log private chat", 
"Log status messages", 
"Log system messages", 
"Log uploads", 
"Logging", 
"Advanced\\Logs", 
"Ask what to do when a magnet link is detected.", 
"Max filelist size", 
"Max hash speed", 
"Max tab rows", 
"Minimize to tray", 
"Name", 
"Connection settings", 
"Don't send the away message to bots", 
"Note; Files appear in the share only after they've been hashed!", 
"Search for files with TTH root only as standard", 
"Open new window when using /join", 
"Always open help file with this dialog", 
"Options", 
"Other queue options", 
"Outgoing connection settings", 
"Don't allow hub/UPnP to override", 
"Personal Information", 
"Make an annoying sound every time a private message is received", 
"Make an annoying sound when a private message window is opened", 
"PM history", 
"Open new file list windows in the background", 
"Open new private message windows in the background", 
"Open private messages from the hub in their own window", 
"Open private messages from bots in their own window", 
"Open private messages in their own window", 
"Ports", 
"Popup box to input password for hubs", 
"Public Hubs list", 
"HTTP Proxy (for hublist only)", 
"Public Hubs list URL", 
"Downloads\\Queue", 
"Rename", 
"Note; most of these options require that you restart DC++", 
"Rollback", 
"Search history", 
"Select &text style", 
"Select &window color", 
"Send unknown /commands to the hub", 
"Enable automatic SFV checking", 
"Share hidden files", 
"Total size:", 
"Shared directories", 
"Show joins / parts in chat by default", 
"Show progress bars for transfers", 
"Skip zero-byte files", 
"Use small send buffer (enable if uploads slow downloads a lot)", 
"SOCKS5", 
"Socks IP", 
"Port", 
"Use SOCKS5 server to resolve host names", 
"Login", 
"Sounds", 
"Note; because of changing download speeds, this is not 100% accurate...", 
"View status messages in main chat", 
"TCP", 
"TLS", 
"Mini slot size", 
"Autoprio settings", 
"Highest prio max size", 
"High prio max size", 
"Normal prio max size", 
"Low prio max size", 
"Set lowest prio for newly added files larger than Low prio size", 
"Show timestamps in chat by default", 
"Set timestamps", 
"Toggle window when selecting an active tab", 
"UDP", 
"Unfinished downloads directory", 
"Line speed (upload)", 
"Sharing", 
"Automatically open an extra slot if speed is below (0 = disable)", 
"Upload slots", 
"Register with Windows to handle dchub:// and adc:// URL links", 
"Register with Windows to handle magnet: URI links", 
"Use CTRL for line history", 
"Use OEM monospaced font for viewing text files", 
"Use system icons when browsing files (slows browsing down a bit)", 
"Advanced\\User Commands", 
"Appearance\\Windows", 
"Window options", 
"Write buffer size", 
"Sort all downloads first", 
"Use TLS when remote client supports it", 
"CRC32 inconsistency (SFV-Check)", 
"Shared", 
"Shared Files", 
"Size", 
"New virtual name matches old name, skipping...", 
"Slot granted", 
"Slots", 
"Slots set", 
"Socks server authentication failed (bad login / password?)", 
"The socks server doesn't support login / password authentication", 
"The socks server failed establish a connection", 
"The socks server requires authentication", 
"Failed to set up the socks server for UDP relay (check socks address and port)", 
"Remote client does not fully support TTH - cannot download", 
"Source too slow", 
"Source Type", 
"Specify a search string", 
"Specify a server to connect to", 
"Specify a URL", 
"Speed", 
"Status", 
"Stored password sent...", 
"System Log", 
"Tag", 
"Target filename too long", 
"Unable to open TCP/TLS port. File transfers will not work correctly until you change settings or turn off any application that might be using the TCP/TLS port", 
"TiB", 
"Time", 
"Time left", 
"Timestamps disabled", 
"Timestamps enabled", 
"More data was sent than was expected", 
"Total: ", 
"A file with the same hash already exists in your share", 
"TTH inconsistency", 
"TTH Root", 
"Type", 
"Unable to open UDP port. Searching will not work correctly until you change settings or turn off any application that might be using the UDP port", 
"Unable to create thread", 
"Unable to open filelist: ", 
"Unable to rename ", 
"Unable to send file ", 
"Unknown", 
"Unknown address", 
"Unknown command: ", 
"Unknown error: 0x%x", 
"Unsupported filelist format", 
"Upload finished, idle...", 
"Upload starting...", 
"Uploaded %s (%.01f%%) in %s", 
" uploaded to ", 
"Uploads", 
"Failed to create port mappings. Please set up your NAT yourself.", 
"Failed to remove port mappings", 
"Failed to get external IP via  UPnP. Please set it yourself.", 
"User", 
"Chat", 
"Command", 
"Context", 
"Filelist Menu", 
"Hub IP / DNS (empty = all, 'op' = where operator)", 
"Hub Menu", 
"Send once per nick", 
"Parameters", 
"PM", 
"Text sent to hub", 
"Raw", 
"Search Menu", 
"To", 
"Command Type", 
"User Menu", 
"Create / Modify Command", 
"User Description", 
"User offline", 
"User went offline", 
"Users", 
"Video", 
"View as text", 
"Virtual name", 
"Virtual directory name already exists", 
"Name under which the others see the directory", 
"Waiting...", 
"Waiting to retry...", 
"Waiting Users", 
"Waiting (User online)", 
"Waiting (%d of %d users online)", 
"Yes", 
"You are being redirected to ", 
};
string ResourceManager::names[] = {
"Active", 
"ActiveSearchString", 
"Add", 
"AddToFavorites", 
"Added", 
"AdlSearch", 
"AdlsDestination", 
"AdlsDiscard", 
"AdlsDownload", 
"AdlsEnabled", 
"AdlsFullPath", 
"AdlsProperties", 
"AdlsSearchString", 
"AdlsSizeMax", 
"AdlsSizeMin", 
"AdlsType", 
"AdlsUnits", 
"AllDownloadSlotsTaken", 
"AllUsersOffline", 
"All3UsersOffline", 
"All4UsersOffline", 
"All", 
"Any", 
"AtLeast", 
"AtMost", 
"Audio", 
"AutoConnect", 
"AutoGrant", 
"Average", 
"Away", 
"AwayModeOff", 
"AwayModeOn", 
"B", 
"BanUser", 
"BothUsersOffline", 
"Bps", 
"Browse", 
"BrowseAccel", 
"BrowseFileList", 
"CertificateNotTrusted", 
"CertificateGenerationFailed", 
"ChooseFolder", 
"Cid", 
"Close", 
"CloseConnection", 
"ClosingConnection", 
"Compressed", 
"CompressionError", 
"CommandTooLong", 
"Configure", 
"Connect", 
"ConnectFavuserHub", 
"Connected", 
"Connecting", 
"ConnectingForced", 
"ConnectingTo", 
"Connection", 
"ConnectionClosed", 
"ConnectionTimeout", 
"ConfiguredHubLists", 
"CopyFilename", 
"CopyHub", 
"CopyMagnet", 
"CopyNick", 
"CouldNotOpenTargetFile", 
"Count", 
"Country", 
"CrcChecked", 
"DecompressionError", 
"Description", 
"Destination", 
"Directory", 
"DirectoryAlreadyShared", 
"DirectoryAddError", 
"DiscFull", 
"DisconnectUser", 
"Disconnected", 
"DisconnectedUser", 
"Document", 
"Done", 
"DontRemoveSlashPassword", 
"DontShareTempDirectory", 
"Download", 
"DownloadFailed", 
"DownloadFinishedIdle", 
"DownloadQueue", 
"DownloadStarting", 
"DownloadTo", 
"DownloadWholeDir", 
"DownloadWholeDirTo", 
"Downloaded", 
"DownloadedBytes", 
"DownloadedFrom", 
"Downloading", 
"DownloadingHubList", 
"DownloadingList", 
"Downloads", 
"DuplicateFileNotShared", 
"DuplicateMatch", 
"DuplicateSource", 
"Edit", 
"EditAccel", 
"Email", 
"EnterNick", 
"EnterPassword", 
"EnterReason", 
"EnterSearchString", 
"EnterServer", 
"Errors", 
"ErrorCreatingHashDataFile", 
"ErrorCreatingRegistryKeyAdc", 
"ErrorCreatingRegistryKeyDchub", 
"ErrorCreatingRegistryKeyMagnet", 
"ErrorHashing", 
"ErrorSavingHash", 
"ExactSize", 
"Executable", 
"FailedToLoadCertificate", 
"FailedToLoadPrivateKey", 
"FavJoinShowingOff", 
"FavJoinShowingOn", 
"FavoriteDirName", 
"FavoriteDirNameLong", 
"FavoriteHubAdded", 
"FavoriteHubAlreadyExists", 
"FavoriteHubDoesNotExist", 
"FavoriteHubIdentity", 
"FavoriteHubProperties", 
"FavoriteHubRemoved", 
"FavoriteHubs", 
"FavoriteUserAdded", 
"FavoriteUsers", 
"File", 
"Files", 
"FileHasNoTth", 
"FileIsAlreadyQueued", 
"FileListDiff", 
"FileListRefreshFailed", 
"FileListRefreshFinished", 
"FileListRefreshInitiated", 
"FileListRefrreshInProgress", 
"FileNotAvailable", 
"FileType", 
"FileWithDifferentSize", 
"FileWithDifferentTth", 
"Filename", 
"FilesLeft", 
"FilesPerHour", 
"Filter", 
"Filtered", 
"Find", 
"FinishedDownloads", 
"FinishedUploads", 
"ForbiddenDollarFile", 
"ForceAttempt", 
"Gib", 
"GetFileList", 
"GoToDirectory", 
"GrantExtraSlot", 
"HashDatabase", 
"HashProgress", 
"HashProgressBackground", 
"HashProgressStats", 
"HashProgressText", 
"HashReadFailed", 
"HashRebuilt", 
"HashingFailed", 
"HashingFinished", 
"High", 
"Highest", 
"HitRatio", 
"Hits", 
"Hub", 
"Hubs", 
"HubAddress", 
"HubListDownloaded", 
"HubListEdit", 
"HubName", 
"HubList", 
"HubPassword", 
"HubUsers", 
"IgnoreTthSearches", 
"IgnoredMessage", 
"IncompleteFavHub", 
"InvalidListname", 
"InvalidNumberOfSlots", 
"InvalidTargetFile", 
"InvalidTree", 
"Ip", 
"IpBare", 
"Items", 
"JoinShowingOff", 
"JoinShowingOn", 
"Joins", 
"Kib", 
"Kibps", 
"KickUser", 
"LargerTargetFileExists", 
"LastChange", 
"LastHub", 
"LastSeen", 
"Left", 
"ListenerFailed", 
"Loading", 
"LookupAtBitzi", 
"Low", 
"Lowest", 
"MagnetDlgFile", 
"MagnetDlgHash", 
"MagnetDlgNothing", 
"MagnetDlgQueue", 
"MagnetDlgRemember", 
"MagnetDlgSearch", 
"MagnetDlgTextBad", 
"MagnetDlgTextGood", 
"MagnetDlgTitle", 
"MagnetHandlerDesc", 
"MagnetHandlerRoot", 
"MagnetShellDesc", 
"MatchQueue", 
"MatchedFiles", 
"MaxHubs", 
"MaxSize", 
"MaxUsers", 
"MinSize", 
"Mib", 
"Mibps", 
"Mibitsps", 
"MenuAbout", 
"MenuAdlSearch", 
"MenuArrange", 
"MenuCascade", 
"MenuChangelog", 
"MenuCloseAllDirList", 
"MenuCloseAllOfflinePm", 
"MenuCloseAllPm", 
"MenuCloseAllSearchframe", 
"MenuCloseDisconnected", 
"MenuContents", 
"MenuDiscuss", 
"MenuDonate", 
"MenuDownloadQueue", 
"MenuExit", 
"MenuFaq", 
"MenuFavoriteHubs", 
"MenuFavoriteUsers", 
"MenuFile", 
"MenuFollowRedirect", 
"MenuHashProgress", 
"MenuHelp", 
"MenuHelpDownloads", 
"MenuHelpGeoipfile", 
"MenuHelpForum", 
"MenuHelpTranslations", 
"MenuHomepage", 
"MenuHorizontalTile", 
"MenuMinimizeAll", 
"MenuRestoreAll", 
"MenuNetworkStatistics", 
"MenuNotepad", 
"MenuOpenDownloadsDir", 
"MenuOpenFileList", 
"MenuOpenMatchAll", 
"MenuOpenOwnList", 
"MenuPublicHubs", 
"MenuQuickConnect", 
"MenuReconnect", 
"MenuRefreshFileList", 
"MenuReportBug", 
"MenuRequestFeature", 
"MenuSearch", 
"MenuSearchSpy", 
"MenuSettings", 
"MenuShow", 
"MenuStatusBar", 
"MenuSystemLog", 
"MenuToolbar", 
"MenuTransferView", 
"MenuVerticalTile", 
"MenuView", 
"MenuWindow", 
"MinShare", 
"MinSlots", 
"Move", 
"MoveDown", 
"MoveUp", 
"NetworkStatistics", 
"New", 
"Next", 
"Nick", 
"NickTaken", 
"NickUnknown", 
"NoCertificateFileSet", 
"NoCrc32Match", 
"NoDirectorySpecified", 
"NoDownloadsFromSelf", 
"NoDownloadsFromPassive", 
"NoErrors", 
"NoMatches", 
"NoSlotsAvailable", 
"NoStr", 
"NoUsers", 
"NoUsersToDownloadFrom", 
"Normal", 
"NotListening", 
"Notepad", 
"Offline", 
"Online", 
"OnlyFreeSlots", 
"OnlyTlsAllowed", 
"OnlyTth", 
"OnlyWhereOp", 
"Open", 
"OpenDownloadPage", 
"OpenFolder", 
"OperatingSystemNotCompatible", 
"OutOfBufferSpace", 
"Parts", 
"PassiveUser", 
"Password", 
"Path", 
"Paused", 
"Pib", 
"Picture", 
"Port", 
"PreparingFileList", 
"PressFollow", 
"Priority", 
"PrivateMessage", 
"PrivateMessageFrom", 
"Properties", 
"PublicHubs", 
"Purge", 
"QuickConnect", 
"Rating", 
"Ratio", 
"ReaddSource", 
"ReallyExit", 
"ReallyRemove", 
"Redirect", 
"RedirectAlreadyConnected", 
"RedirectUser", 
"Refresh", 
"RefreshUserList", 
"Reliability", 
"Remove", 
"RemoveAll", 
"RemoveAllSubdirectories", 
"RemoveFromAll", 
"RemoveSource", 
"RenamedTo", 
"RollbackInconsistency", 
"Running", 
"S", 
"Search", 
"SearchFor", 
"SearchForAlternates", 
"SearchForFile", 
"SearchOptions", 
"SearchSpamFrom", 
"SearchSpy", 
"SearchString", 
"SearchingFor", 
"SearchingReady", 
"SearchingWait", 
"SeekBeyondEnd", 
"SendPrivateMessage", 
"Separator", 
"Server", 
"SetPriority", 
"Settings", 
"SettingsAddFinishedInstantly", 
"SettingsAddFolder", 
"SettingsAdlsBreakOnFirst", 
"SettingsAdvanced", 
"SettingsAdvanced3", 
"SettingsAdvancedResume", 
"SettingsAdvancedSettings", 
"SettingsAllowUntrustedClients", 
"SettingsAllowUntrustedHubs", 
"SettingsAntiFrag", 
"SettingsAppearance", 
"SettingsAppearance2", 
"SettingsAutodropAutodropsettings", 
"SettingsAutodropSpeed", 
"SettingsAutodropInterval", 
"SettingsAutodropElapsed", 
"SettingsAutodropInactivity", 
"SettingsAutodropMinsources", 
"SettingsAutodropFilesize", 
"SettingsAutodropAll", 
"SettingsAutodropFilelists", 
"SettingsAutodropDisconnect", 
"SettingsAutoAway", 
"SettingsAutoFollow", 
"SettingsAutoKick", 
"SettingsAutoKickNoFavs", 
"SettingsAutoSearch", 
"SettingsAutoSearchAutoMatch", 
"SettingsAutoSearchLimit", 
"SettingsAutoOpen", 
"SettingsAutoRefreshTime", 
"SettingsBindAddress", 
"SettingsBoldOptions", 
"SettingsCertificates", 
"SettingsChange", 
"SettingsClearSearch", 
"SettingsColors", 
"SettingsCommand", 
"SettingsCompressTransfers", 
"SettingsConfigureHubLists", 
"SettingsConfirmDialogOptions", 
"SettingsConfirmExit", 
"SettingsConfirmHubRemoval", 
"SettingsConfirmItemRemoval", 
"SettingsConnectionType", 
"SettingsDefaultAwayMsg", 
"SettingsDirect", 
"SettingsDirectories", 
"SettingsDontDlAlreadyQueued", 
"SettingsDontDlAlreadyShared", 
"SettingsDownloadDirectory", 
"SettingsDownloadLimits", 
"SettingsDownloads", 
"SettingsDownloadsMax", 
"SettingsDownloadsSpeedPause", 
"SettingsExampleText", 
"SettingsExternalIp", 
"SettingsFavShowJoins", 
"SettingsFavoriteDirsPage", 
"SettingsFavoriteDirs", 
"SettingsFileName", 
"SettingsFilterMessages", 
"SettingsFirewallNat", 
"SettingsFirewallPassive", 
"SettingsFirewallUpnp", 
"SettingsFormat", 
"SettingsGeneral", 
"SettingsGetUserCountry", 
"SettingsHubUserCommands", 
"SettingsIgnoreHubPms", 
"SettingsIgnoreBotPms", 
"SettingsIncoming", 
"SettingsKeepLists", 
"SettingsLanguageFile", 
"SettingsListDupes", 
"SettingsLogDownloads", 
"SettingsLogFilelistTransfers", 
"SettingsLogMainChat", 
"SettingsLogPrivateChat", 
"SettingsLogStatusMessages", 
"SettingsLogSystemMessages", 
"SettingsLogUploads", 
"SettingsLogging", 
"SettingsLogs", 
"SettingsMagnetAsk", 
"SettingsMaxFilelistSize", 
"SettingsMaxHashSpeed", 
"SettingsMaxTabRows", 
"SettingsMinimizeTray", 
"SettingsName", 
"SettingsNetwork", 
"SettingsNoAwaymsgToBots", 
"SettingsOnlyHashed", 
"SettingsOnlyTth", 
"SettingsOpenNewWindow", 
"SettingsOpenUserCmdHelp", 
"SettingsOptions", 
"SettingsOtherQueueOptions", 
"SettingsOutgoing", 
"SettingsOverride", 
"SettingsPersonalInformation", 
"SettingsPmBeep", 
"SettingsPmBeepOpen", 
"SettingsPmHistory", 
"SettingsPopunderFilelist", 
"SettingsPopunderPm", 
"SettingsPopupBotPms", 
"SettingsPopupHubPms", 
"SettingsPopupPms", 
"SettingsPorts", 
"SettingsPromptPassword", 
"SettingsPublicHubList", 
"SettingsPublicHubListHttpProxy", 
"SettingsPublicHubListUrl", 
"SettingsQueue", 
"SettingsRenameFolder", 
"SettingsRequiresRestart", 
"SettingsRollback", 
"SettingsSearchHistory", 
"SettingsSelectTextFace", 
"SettingsSelectWindowColor", 
"SettingsSendUnknownCommands", 
"SettingsSfvCheck", 
"SettingsShareHidden", 
"SettingsShareSize", 
"SettingsSharedDirectories", 
"SettingsShowJoins", 
"SettingsShowProgressBars", 
"SettingsSkipZeroByte", 
"SettingsSmallSendBuffer", 
"SettingsSocks5", 
"SettingsSocks5Ip", 
"SettingsSocks5Port", 
"SettingsSocks5Resolve", 
"SettingsSocks5Username", 
"SettingsSounds", 
"SettingsSpeedsNotAccurate", 
"SettingsStatusInChat", 
"SettingsTcpPort", 
"SettingsTlsPort", 
"SettingsTextMinislot", 
"SettingsPrioAutoprio", 
"SettingsPrioHighest", 
"SettingsPrioHigh", 
"SettingsPrioNormal", 
"SettingsPrioLow", 
"SettingsPrioLowest", 
"SettingsTimeStamps", 
"SettingsTimeStampsFormat", 
"SettingsToggleActiveWindow", 
"SettingsUdpPort", 
"SettingsUnfinishedDownloadDirectory", 
"SettingsUploadLineSpeed", 
"SettingsUploads", 
"SettingsUploadsMinSpeed", 
"SettingsUploadsSlots", 
"SettingsUrlHandler", 
"SettingsUrlMagnet", 
"SettingsUseCtrlForLineHistory", 
"SettingsUseOemMonofont", 
"SettingsUseSystemIcons", 
"SettingsUserCommands", 
"SettingsWindows", 
"SettingsWindowsOptions", 
"SettingsWriteBuffer", 
"SettingsAltSortOrder", 
"SettingsUseTls", 
"SfvInconsistency", 
"Shared", 
"SharedFiles", 
"Size", 
"SkipRename", 
"SlotGranted", 
"Slots", 
"SlotsSet", 
"SocksAuthFailed", 
"SocksAuthUnsupported", 
"SocksFailed", 
"SocksNeedsAuth", 
"SocksSetupError", 
"SourceTooOld", 
"SourceTooSlow", 
"SourceType", 
"SpecifySearchString", 
"SpecifyServer", 
"SpecifyUrl", 
"Speed", 
"Status", 
"StoredPasswordSent", 
"SystemLog", 
"Tag", 
"TargetFilenameTooLong", 
"TcpPortBusy", 
"Tib", 
"Time", 
"TimeLeft", 
"TimestampsDisabled", 
"TimestampsEnabled", 
"TooMuchData", 
"Total", 
"TthAlreadyShared", 
"TthInconsistency", 
"TthRoot", 
"Type", 
"UdpPortBusy", 
"UnableToCreateThread", 
"UnableToOpenFilelist", 
"UnableToRename", 
"UnableToSendFile", 
"Unknown", 
"UnknownAddress", 
"UnknownCommand", 
"UnknownError", 
"UnsupportedFilelistFormat", 
"UploadFinishedIdle", 
"UploadStarting", 
"UploadedBytes", 
"UploadedTo", 
"Uploads", 
"UpnpFailedToCreateMappings", 
"UpnpFailedToRemoveMappings", 
"UpnpFailedToGetExternalIp", 
"User", 
"UserCmdChat", 
"UserCmdCommand", 
"UserCmdContext", 
"UserCmdFilelistMenu", 
"UserCmdHub", 
"UserCmdHubMenu", 
"UserCmdOnce", 
"UserCmdParameters", 
"UserCmdPm", 
"UserCmdPreview", 
"UserCmdRaw", 
"UserCmdSearchMenu", 
"UserCmdTo", 
"UserCmdType", 
"UserCmdUserMenu", 
"UserCmdWindow", 
"UserDescription", 
"UserOffline", 
"UserWentOffline", 
"Users", 
"Video", 
"ViewAsText", 
"VirtualName", 
"VirtualNameExists", 
"VirtualNameLong", 
"Waiting", 
"WaitingToRetry", 
"WaitingUsers", 
"WaitingUserOnline", 
"WaitingUsersOnline", 
"YesStr", 
"YouAreBeingRedirected", 
};
